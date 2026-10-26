#include <dolphin.h>
#include <dolphin/os.h>

#include <dolphin/os/OSExec.h>
#include <dolphin/os/OSCache.h>

extern volatile u32 BOOT_REGION_START AT_ADDRESS(0x812FDFF0);
extern volatile u32 BOOT_REGION_END AT_ADDRESS(0x812FDFEC);
extern volatile u8 BOOT_REGION_UNK AT_ADDRESS(0x800030e2);
extern volatile u8 g_unk_800030E2 AT_ADDRESS(0x800030E2);
extern u32 OS_RESET_CODE AT_ADDRESS(0x800030F0);
extern int OS_APPLOADER_ADDR AT_ADDRESS(0x800030F4);

static int Prepared;

// Magic number defines.
#define OS_BOOTINFO_MAGIC 0x0D15EA5E
#define OS_BOOTINFO_MAGIC_JTAG 0xE5207C22
#define OS_DVD_MAGIC_NINTENDO 0xC2339F3D
#define OS_THREAD_STACK_MAGIC 0xDEADBABE

#define OS_BOOTROM_ADDR 0x81300000

static int lbl_803CBD98;
static int CachedApploaderAddr;

typedef struct
{
    u32 _00[0x800];
} ArgsStruct;

#define ARG_SIZE 0x2000

typedef int (*unk3ParamFunc)(void* a, void* b, void* c);
typedef u32 (*unk2ParamFunc)(void* a, void* b);
typedef u32 (*unk1ParamFunc)(void* a);
typedef u32 (*unk0ParamFunc)();

typedef struct
{
    u32 _00;
    u32 _04;
    u32 _08;
    u32 _0C;
    u32 _10;
    u32 _14;
    void* _18;
} _1C_Struct;

static int PackArgs(void* addr, s32 argc, char** argv)
{
    s32 numArgs;
    char* bootInfo2;
    char* ptr;
    char** list;
    u32 i;

    bootInfo2 = (char*)addr;
    memset(bootInfo2, 0, 0x2000);

    if (argc == 0)
    {
        *(u32*)(bootInfo2 + 8) = 0;
    }
    else
    {
        numArgs = argc;
        ptr = bootInfo2 + 0x2000;
        while (--argc >= 0)
        {
            ptr -= strlen(argv[argc]) + 1;
            strcpy(ptr, argv[argc]);
            argv[argc] = (char*)(ptr - bootInfo2);
        }

        ptr = bootInfo2 + ((ptr - bootInfo2) & ~0x3);
        ptr -= ((numArgs + 1) * 4);
        list = (char**)ptr;

        for (i = 0; i < numArgs + 1; i++)
        {
            list[i] = argv[i];
        }

        ptr -= 4;
        *(u32*)ptr = numArgs;

        *(u32*)(bootInfo2 + 8) = (ptr - bootInfo2);
    }

    return 1;
}

typedef void (*runFunc)(void);
#ifdef __MWERKS__ // clang-format off
ASM void Run(register runFunc v)
{
    fralloc    
    bl ICFlashInvalidate
    sync
    isync
    mtlr v
    blr
}
#endif // clang-format on

static void ReadDisc(void* addr, s32 length, s32 offset)
{
    DVDCommandBlock block;

    DVDReadAbsAsyncPrio(&block, addr, length, offset, NULL, 0);

    while (DVDGetCommandBlockStatus(&block))
    {
        if (!DVDCheckDisk())
        {
            __OSDoHotReset(0);
        }
    }
}

static void Callback(s32, DVDCommandBlock*)
{
    Prepared = TRUE;
}

void __OSGetExecParams(OSExecParams* params)
{
    if (0x80000000 <= (u32)__OSExecParams)
    {
        memcpy(params, __OSExecParams, sizeof(OSExecParams));
    }
    else
    {
        params->valid = FALSE;
    }
}

static int GetApploaderPosition(void)
{
    static s32 apploaderPosition;

    u32* tgcHeader;
    s32 apploaderOffsetInTGC;

    if (apploaderPosition != 0)
    {
        return apploaderPosition;
    }

    if (__OSAppLoaderOffset != 0)
    {
        tgcHeader = OSAllocFromArenaLo(0x40, 0x20);
        ReadDisc(tgcHeader, 0x40, __OSAppLoaderOffset);
        apploaderOffsetInTGC = tgcHeader[14];

        apploaderPosition = __OSAppLoaderOffset + apploaderOffsetInTGC;
    }
    else
    {
        apploaderPosition = 0x2440;
    }
    return apploaderPosition;
}

typedef struct
{
    char date[16];
    u32 entry;
    u32 size;
    u32 rebootSize;
    u32 reserved2;
} AppLoaderStruct;

typedef struct
{
    int _00;
    int _04;
    int _08;
    int _0c;
    int _10;
    int _14;
} ApploaderStruct;

#define APPLOADER_ADDR ((void*)0x81200000)

static BOOL IsNewApploader(AppLoaderStruct* header)
{
    return strncmp(header->date, "2004/02/01", 10) > 0 ? TRUE : FALSE;
}

static void __OSBootDolSimple(u32 v, u32 b, void* start, void* end, int argc, u32 count,
                              ArgsStruct* argv)
{
    _1C_Struct* src;
    DVDCommandBlock bloc;
    _1C_Struct* src2;
    ApploaderStruct* allocated;
    struct
    {
        u32 _00;
        u32 _04;
        u32 _08;
        u32 _0C;
        u32 _10;
        u32 _14;
        u32 _1C;
    } _c_LOOKATME;
    int ret;

    int interrupts;

    interrupts = OSDisableInterrupts();
    src = (_1C_Struct*)OSAllocFromArenaLo(sizeof(_1C_Struct), 1);
    src->_00 = 1;
    src->_04 = b;
    src->_0C = (u32)start;
    src->_10 = (u32)end;
    src->_14 = argc;
    if (!argc)
    {
        src->_18 = OSAllocFromArenaLo(ARG_SIZE, 1);
        PackArgs(src->_18, count, (char**)argv);
    }
    DVDInit();
    DVDSetAutoInvalidation(1);
    DVDResume();
    Prepared = 0;
    __DVDPrepareResetAsync(Callback);
    __OSMaskInterrupts(0xffffffe0);
    __OSUnmaskInterrupts(0x400);
    OSEnableInterrupts();
    while (Prepared != 1)
    {
        if (!DVDCheckDisk())
        {
            __OSDoHotReset(0);
        }
    }
    if ((__OSIsGcam == 0))
    {
        if (DVDGetCurrentDiskID()->streaming ? 1 : 0)
        {
            AISetStreamVolLeft(0);
            AISetStreamVolRight(0);
            DVDCancelStreamAsync(&bloc, 0);
            while (DVDGetCommandBlockStatus(&bloc))
            {
                if (!DVDCheckDisk())
                {
                    __OSDoHotReset(0);
                }
            }
            AISetStreamPlayState(0);
        }
    }

    src2 = (_1C_Struct*)OSAllocFromArenaLo(0x20, 0x20);
    ReadDisc(src2, 0x20, GetApploaderPosition());

    ReadDisc(APPLOADER_ADDR, ROUND_UP(src2->_14, 32), GetApploaderPosition() + 0x20);
    ICInvalidateRange(APPLOADER_ADDR, ROUND_UP(src2->_14, 32));

    if (strncmp((char*)src2, "2004/02/01", 10) > 0 ? 1 : 0)
    {
        if (v + 0x10000 == 0xffff)
        {
            DVDCommandBlock block2;
            DVDCommandBlock bloc;
            int* alloc;
            int thisCachedApploaderAddr = CachedApploaderAddr;
            switch (thisCachedApploaderAddr)
            {
            case 0:
                if (OS_APPLOADER_ADDR)
                {
                    argv = (void*)OSAllocFromArenaLo(0x40, 0x20);
                    DVDReadAbsAsyncPrio(&bloc, argv, 0x40, OS_APPLOADER_ADDR, 0, 0);

                    while (DVDGetCommandBlockStatus(&bloc))
                    {
                        if (!DVDCheckDisk())
                        {
                            __OSDoHotReset(0);
                        }
                    }

                    CachedApploaderAddr = OS_APPLOADER_ADDR + ((u32*)argv)[0xe];
                }
                else
                {
                    CachedApploaderAddr = 0x2440;
                }
                thisCachedApploaderAddr = CachedApploaderAddr;
            }
            argv = (ArgsStruct*)(thisCachedApploaderAddr + argv->_00[5]);
            argv = (ArgsStruct*)(((u32*)argv) + 8);
        }
        src->_08 = v;
        ((unk3ParamFunc)argv->_00[4])(&_c_LOOKATME._04, &_c_LOOKATME._04, &_c_LOOKATME._04);

        src2 = OSAllocFromArenaLo(sizeof(_1C_Struct), 1);
        memcpy(src2, argv, sizeof(_1C_Struct));

        OS_RESET_CODE = (u32)src2;

        ((unk1ParamFunc)_c_LOOKATME._04)(OSReport);

        OSSetArenaLo(src2);
        while (
            ((unk3ParamFunc)_c_LOOKATME._00)(&_c_LOOKATME._04, &_c_LOOKATME._08, &_c_LOOKATME._0C))
        {
            DVDCommandBlock v;
            DVDReadAbsAsyncPrio(&v, (void*)_c_LOOKATME._04, (u32)_c_LOOKATME._08,
                                (u32)_c_LOOKATME._0C, 0, 0);
            while (DVDGetCommandBlockStatus(&v))
            {
                if (!DVDCheckDisk())
                {
                    __OSDoHotReset(0);
                }
            }
        }

        {
            _1C_Struct* s;
            ret = ((unk0ParamFunc)_c_LOOKATME._08)();

            s = OSAllocFromArenaLo(sizeof(_1C_Struct), 1);
            memcpy(s, src, sizeof(_1C_Struct));
            OS_RESET_CODE = (u32)s;
            __PIRegs[9] = 7;
            OSDisableInterrupts();
            Run((runFunc)ret);
            return;
        }
    }

    BOOT_REGION_START = (u32)start;
    BOOT_REGION_END = (u32)end;
    BOOT_REGION_UNK = 1;
    {
        int newAppPos = GetApploaderPosition() + 0x20 + argv->_00[5];
        DVDReadAbsAsyncPrio(&bloc, (void*)OS_BOOTROM_ADDR, ROUND_UP(argv->_00[6], 32), newAppPos, 0,
                            0);
    }
    while (DVDGetCommandBlockStatus(&bloc))
    {
        if (!DVDCheckDisk())
        {
            __OSDoHotReset(0);
        }
    }

    ICInvalidateRange((void*)OS_BOOTROM_ADDR, ROUND_UP(argv->_00[6], 32));
    OSDisableInterrupts();
    ICFlashInvalidate();
    Run((runFunc)OS_BOOTROM_ADDR);
}

void __OSBootDol(u32 doloffset, u32 restartCode, const char** argv)
{
    char doloffInString[20];
    s32 argvlen;
    char** argvToPass;
    s32 i;
    void* saveStart;
    void* saveEnd;

    OSGetSaveRegion(&saveStart, &saveEnd);

    sprintf(doloffInString, "%d", doloffset);
    argvlen = 0;

    if (argv != 0)
    {
        while (argv[argvlen] != 0)
        {
            argvlen++;
        }
    }

    argvlen++;
    argvToPass = OSAllocFromArenaLo((argvlen + 1) * 4, 1);
    *argvToPass = doloffInString;

    for (i = 1; i < argvlen; i++)
    {
        argvToPass[i] = (char*)argv[i - 1];
    }

    __OSBootDolSimple(-1, restartCode, saveStart, saveEnd, FALSE, argvlen, (ArgsStruct*)argvToPass);
}
