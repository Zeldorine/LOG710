##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=MemoryManager
ConfigurationName      :=Debug
WorkspacePath          :=/home/zeldorine/LOG710/LOG710/LAB03
ProjectPath            :=/home/zeldorine/LOG710/LOG710/LAB03/MemoryManager
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Zeldorine
Date                   :=20/11/17
CodeLitePath           :=/home/zeldorine/.codelite
LinkerName             :=gcc
SharedObjectLinkerName :=gcc -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="MemoryManager.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := gcc
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/logger.c$(ObjectSuffix) $(IntermediateDirectory)/linkedList.c$(ObjectSuffix) $(IntermediateDirectory)/allocationStrategy.c$(ObjectSuffix) $(IntermediateDirectory)/linkedListTest.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/zeldorine/LOG710/LOG710/LAB03/MemoryManager/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM main.c

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) main.c

$(IntermediateDirectory)/logger.c$(ObjectSuffix): logger.c $(IntermediateDirectory)/logger.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/zeldorine/LOG710/LOG710/LAB03/MemoryManager/logger.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/logger.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/logger.c$(DependSuffix): logger.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/logger.c$(ObjectSuffix) -MF$(IntermediateDirectory)/logger.c$(DependSuffix) -MM logger.c

$(IntermediateDirectory)/logger.c$(PreprocessSuffix): logger.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/logger.c$(PreprocessSuffix) logger.c

$(IntermediateDirectory)/linkedList.c$(ObjectSuffix): linkedList.c $(IntermediateDirectory)/linkedList.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/zeldorine/LOG710/LOG710/LAB03/MemoryManager/linkedList.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/linkedList.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/linkedList.c$(DependSuffix): linkedList.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/linkedList.c$(ObjectSuffix) -MF$(IntermediateDirectory)/linkedList.c$(DependSuffix) -MM linkedList.c

$(IntermediateDirectory)/linkedList.c$(PreprocessSuffix): linkedList.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/linkedList.c$(PreprocessSuffix) linkedList.c

$(IntermediateDirectory)/allocationStrategy.c$(ObjectSuffix): allocationStrategy.c $(IntermediateDirectory)/allocationStrategy.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/zeldorine/LOG710/LOG710/LAB03/MemoryManager/allocationStrategy.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/allocationStrategy.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/allocationStrategy.c$(DependSuffix): allocationStrategy.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/allocationStrategy.c$(ObjectSuffix) -MF$(IntermediateDirectory)/allocationStrategy.c$(DependSuffix) -MM allocationStrategy.c

$(IntermediateDirectory)/allocationStrategy.c$(PreprocessSuffix): allocationStrategy.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/allocationStrategy.c$(PreprocessSuffix) allocationStrategy.c

$(IntermediateDirectory)/linkedListTest.c$(ObjectSuffix): linkedListTest.c $(IntermediateDirectory)/linkedListTest.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/zeldorine/LOG710/LOG710/LAB03/MemoryManager/linkedListTest.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/linkedListTest.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/linkedListTest.c$(DependSuffix): linkedListTest.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/linkedListTest.c$(ObjectSuffix) -MF$(IntermediateDirectory)/linkedListTest.c$(DependSuffix) -MM linkedListTest.c

$(IntermediateDirectory)/linkedListTest.c$(PreprocessSuffix): linkedListTest.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/linkedListTest.c$(PreprocessSuffix) linkedListTest.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


