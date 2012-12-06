!include <win32.mak>


EXE = program.exe

EXE: dll
	csc /nologo /t:exe /out:$(EXE) /reference:foo.DLL main.cs

clean: dll_clean
	del $(EXE)

#-----------------------------------------------------------------------
NET4_ASM = "C:\Program Files\Reference Assemblies\Microsoft\Framework\.NETFramework\v4.0"

DLL = foo.dll
DLL_INCLUDES = /I.\include
DLL_SRCS = foo.cpp
DLL_OBJS = $(DLL_SRCS:.cpp=.obj)
DLL_FLAGS = $(DLL_INCLUDES) /AI$(NET4_ASM) /Zi /clr /nologo /W3 /WX- /Od /Oy- /D WIN32 /D _DEBUG /D _WINDLL /D _UNICODE /D UNICODE /EHa /MDd /GS /fp:precise /Zc:wchar_t /Zc:forScope
DLL_OUT = .\\
DLL_NAME = $(DLL:.dll=)

DLL_LIBS = kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib


dll: $(DLL)

# /Fo$(DLL_OUT) /Fd$(DLL_OUT)vc100.pdb /
.cpp.obj:
	$(CC) /c $(DLL_FLAGS) /TP /analyze- /errorReport:prompt /clr:nostdlib $<

$(DLL): $(DLL_OBJS)
	$(link) /ERRORREPORT:PROMPT /OUT:"$(DLL_OUT)$(DLL)" /INCREMENTAL /NOLOGO $(DLL_LIBS) /MANIFEST /ManifestFile:"$(DLL_OUT)$(DLL).intermediate.manifest" /MANIFESTUAC:"level='asInvoker' uiAccess='false'" /DEBUG /PDB:"$(DLL_OUT)$(DLL_NAME).pdb" /ASSEMBLYDEBUG /TLBID:1 /DYNAMICBASE /FIXED:NO /NXCOMPAT /MACHINE:X86 /DLL $(DLL_OBJS)

dll_clean:
	del $(DLL_OUT)$(DLL) $(DLL_OUT)$(DLL).intermediate.manifest $(DLL_OBJS) $(DLL_OUT)$(DLL_NAME).pdb $(DLL:.dll=.ilk) vc100.pdb
	

