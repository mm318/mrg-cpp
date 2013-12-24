##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=mrg_axon_model
ConfigurationName      :=Release
WorkspacePath          := .
ProjectPath            := .
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
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
ObjectsFileList        :="mrg_axon_model.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)./src/libs 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -O2 -Wall $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files (x86)\CodeLite
Objects0=$(IntermediateDirectory)/src_MRG_init$(ObjectSuffix) $(IntermediateDirectory)/src_MRG_main$(ObjectSuffix) $(IntermediateDirectory)/src_MRG_ode$(ObjectSuffix) $(IntermediateDirectory)/src_utils$(ObjectSuffix) $(IntermediateDirectory)/cvode_cvode$(ObjectSuffix) $(IntermediateDirectory)/cvode_cvode_band$(ObjectSuffix) $(IntermediateDirectory)/cvode_cvode_bandpre$(ObjectSuffix) $(IntermediateDirectory)/cvode_cvode_bbdpre$(ObjectSuffix) $(IntermediateDirectory)/cvode_cvode_dense$(ObjectSuffix) $(IntermediateDirectory)/cvode_cvode_diag$(ObjectSuffix) \
	$(IntermediateDirectory)/cvode_cvode_direct$(ObjectSuffix) $(IntermediateDirectory)/cvode_cvode_io$(ObjectSuffix) $(IntermediateDirectory)/cvode_cvode_spbcgs$(ObjectSuffix) $(IntermediateDirectory)/cvode_cvode_spgmr$(ObjectSuffix) $(IntermediateDirectory)/cvode_cvode_spils$(ObjectSuffix) $(IntermediateDirectory)/cvode_cvode_sptfqmr$(ObjectSuffix) $(IntermediateDirectory)/nvec_ser_fnvector_serial$(ObjectSuffix) $(IntermediateDirectory)/nvec_ser_nvector_serial$(ObjectSuffix) $(IntermediateDirectory)/sundials_sundials_band$(ObjectSuffix) $(IntermediateDirectory)/sundials_sundials_dense$(ObjectSuffix) \
	$(IntermediateDirectory)/sundials_sundials_direct$(ObjectSuffix) $(IntermediateDirectory)/sundials_sundials_iterative$(ObjectSuffix) $(IntermediateDirectory)/sundials_sundials_math$(ObjectSuffix) $(IntermediateDirectory)/sundials_sundials_nvector$(ObjectSuffix) $(IntermediateDirectory)/sundials_sundials_spbcgs$(ObjectSuffix) $(IntermediateDirectory)/sundials_sundials_spgmr$(ObjectSuffix) $(IntermediateDirectory)/sundials_sundials_sptfqmr$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Release"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_MRG_init$(ObjectSuffix): src/MRG_init.cpp $(IntermediateDirectory)/src_MRG_init$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "./src/MRG_init.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_MRG_init$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_MRG_init$(DependSuffix): src/MRG_init.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_MRG_init$(ObjectSuffix) -MF$(IntermediateDirectory)/src_MRG_init$(DependSuffix) -MM "src/MRG_init.cpp"

$(IntermediateDirectory)/src_MRG_init$(PreprocessSuffix): src/MRG_init.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_MRG_init$(PreprocessSuffix) "src/MRG_init.cpp"

$(IntermediateDirectory)/src_MRG_main$(ObjectSuffix): src/MRG_main.cpp $(IntermediateDirectory)/src_MRG_main$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "./src/MRG_main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_MRG_main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_MRG_main$(DependSuffix): src/MRG_main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_MRG_main$(ObjectSuffix) -MF$(IntermediateDirectory)/src_MRG_main$(DependSuffix) -MM "src/MRG_main.cpp"

$(IntermediateDirectory)/src_MRG_main$(PreprocessSuffix): src/MRG_main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_MRG_main$(PreprocessSuffix) "src/MRG_main.cpp"

$(IntermediateDirectory)/src_MRG_ode$(ObjectSuffix): src/MRG_ode.cpp $(IntermediateDirectory)/src_MRG_ode$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "./src/MRG_ode.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_MRG_ode$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_MRG_ode$(DependSuffix): src/MRG_ode.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_MRG_ode$(ObjectSuffix) -MF$(IntermediateDirectory)/src_MRG_ode$(DependSuffix) -MM "src/MRG_ode.cpp"

$(IntermediateDirectory)/src_MRG_ode$(PreprocessSuffix): src/MRG_ode.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_MRG_ode$(PreprocessSuffix) "src/MRG_ode.cpp"

$(IntermediateDirectory)/src_utils$(ObjectSuffix): src/utils.cpp $(IntermediateDirectory)/src_utils$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "./src/utils.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_utils$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_utils$(DependSuffix): src/utils.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_utils$(ObjectSuffix) -MF$(IntermediateDirectory)/src_utils$(DependSuffix) -MM "src/utils.cpp"

$(IntermediateDirectory)/src_utils$(PreprocessSuffix): src/utils.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_utils$(PreprocessSuffix) "src/utils.cpp"

$(IntermediateDirectory)/cvode_cvode$(ObjectSuffix): src/libs/cvode/cvode.c $(IntermediateDirectory)/cvode_cvode$(DependSuffix)
	$(CC) $(SourceSwitch) "./src/libs/cvode/cvode.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cvode_cvode$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cvode_cvode$(DependSuffix): src/libs/cvode/cvode.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cvode_cvode$(ObjectSuffix) -MF$(IntermediateDirectory)/cvode_cvode$(DependSuffix) -MM "src/libs/cvode/cvode.c"

$(IntermediateDirectory)/cvode_cvode$(PreprocessSuffix): src/libs/cvode/cvode.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cvode_cvode$(PreprocessSuffix) "src/libs/cvode/cvode.c"

$(IntermediateDirectory)/cvode_cvode_band$(ObjectSuffix): src/libs/cvode/cvode_band.c $(IntermediateDirectory)/cvode_cvode_band$(DependSuffix)
	$(CC) $(SourceSwitch) "./src/libs/cvode/cvode_band.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cvode_cvode_band$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cvode_cvode_band$(DependSuffix): src/libs/cvode/cvode_band.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cvode_cvode_band$(ObjectSuffix) -MF$(IntermediateDirectory)/cvode_cvode_band$(DependSuffix) -MM "src/libs/cvode/cvode_band.c"

$(IntermediateDirectory)/cvode_cvode_band$(PreprocessSuffix): src/libs/cvode/cvode_band.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cvode_cvode_band$(PreprocessSuffix) "src/libs/cvode/cvode_band.c"

$(IntermediateDirectory)/cvode_cvode_bandpre$(ObjectSuffix): src/libs/cvode/cvode_bandpre.c $(IntermediateDirectory)/cvode_cvode_bandpre$(DependSuffix)
	$(CC) $(SourceSwitch) "./src/libs/cvode/cvode_bandpre.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cvode_cvode_bandpre$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cvode_cvode_bandpre$(DependSuffix): src/libs/cvode/cvode_bandpre.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cvode_cvode_bandpre$(ObjectSuffix) -MF$(IntermediateDirectory)/cvode_cvode_bandpre$(DependSuffix) -MM "src/libs/cvode/cvode_bandpre.c"

$(IntermediateDirectory)/cvode_cvode_bandpre$(PreprocessSuffix): src/libs/cvode/cvode_bandpre.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cvode_cvode_bandpre$(PreprocessSuffix) "src/libs/cvode/cvode_bandpre.c"

$(IntermediateDirectory)/cvode_cvode_bbdpre$(ObjectSuffix): src/libs/cvode/cvode_bbdpre.c $(IntermediateDirectory)/cvode_cvode_bbdpre$(DependSuffix)
	$(CC) $(SourceSwitch) "./src/libs/cvode/cvode_bbdpre.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cvode_cvode_bbdpre$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cvode_cvode_bbdpre$(DependSuffix): src/libs/cvode/cvode_bbdpre.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cvode_cvode_bbdpre$(ObjectSuffix) -MF$(IntermediateDirectory)/cvode_cvode_bbdpre$(DependSuffix) -MM "src/libs/cvode/cvode_bbdpre.c"

$(IntermediateDirectory)/cvode_cvode_bbdpre$(PreprocessSuffix): src/libs/cvode/cvode_bbdpre.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cvode_cvode_bbdpre$(PreprocessSuffix) "src/libs/cvode/cvode_bbdpre.c"

$(IntermediateDirectory)/cvode_cvode_dense$(ObjectSuffix): src/libs/cvode/cvode_dense.c $(IntermediateDirectory)/cvode_cvode_dense$(DependSuffix)
	$(CC) $(SourceSwitch) "./src/libs/cvode/cvode_dense.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cvode_cvode_dense$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cvode_cvode_dense$(DependSuffix): src/libs/cvode/cvode_dense.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cvode_cvode_dense$(ObjectSuffix) -MF$(IntermediateDirectory)/cvode_cvode_dense$(DependSuffix) -MM "src/libs/cvode/cvode_dense.c"

$(IntermediateDirectory)/cvode_cvode_dense$(PreprocessSuffix): src/libs/cvode/cvode_dense.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cvode_cvode_dense$(PreprocessSuffix) "src/libs/cvode/cvode_dense.c"

$(IntermediateDirectory)/cvode_cvode_diag$(ObjectSuffix): src/libs/cvode/cvode_diag.c $(IntermediateDirectory)/cvode_cvode_diag$(DependSuffix)
	$(CC) $(SourceSwitch) "./src/libs/cvode/cvode_diag.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cvode_cvode_diag$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cvode_cvode_diag$(DependSuffix): src/libs/cvode/cvode_diag.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cvode_cvode_diag$(ObjectSuffix) -MF$(IntermediateDirectory)/cvode_cvode_diag$(DependSuffix) -MM "src/libs/cvode/cvode_diag.c"

$(IntermediateDirectory)/cvode_cvode_diag$(PreprocessSuffix): src/libs/cvode/cvode_diag.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cvode_cvode_diag$(PreprocessSuffix) "src/libs/cvode/cvode_diag.c"

$(IntermediateDirectory)/cvode_cvode_direct$(ObjectSuffix): src/libs/cvode/cvode_direct.c $(IntermediateDirectory)/cvode_cvode_direct$(DependSuffix)
	$(CC) $(SourceSwitch) "./src/libs/cvode/cvode_direct.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cvode_cvode_direct$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cvode_cvode_direct$(DependSuffix): src/libs/cvode/cvode_direct.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cvode_cvode_direct$(ObjectSuffix) -MF$(IntermediateDirectory)/cvode_cvode_direct$(DependSuffix) -MM "src/libs/cvode/cvode_direct.c"

$(IntermediateDirectory)/cvode_cvode_direct$(PreprocessSuffix): src/libs/cvode/cvode_direct.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cvode_cvode_direct$(PreprocessSuffix) "src/libs/cvode/cvode_direct.c"

$(IntermediateDirectory)/cvode_cvode_io$(ObjectSuffix): src/libs/cvode/cvode_io.c $(IntermediateDirectory)/cvode_cvode_io$(DependSuffix)
	$(CC) $(SourceSwitch) "./src/libs/cvode/cvode_io.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cvode_cvode_io$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cvode_cvode_io$(DependSuffix): src/libs/cvode/cvode_io.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cvode_cvode_io$(ObjectSuffix) -MF$(IntermediateDirectory)/cvode_cvode_io$(DependSuffix) -MM "src/libs/cvode/cvode_io.c"

$(IntermediateDirectory)/cvode_cvode_io$(PreprocessSuffix): src/libs/cvode/cvode_io.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cvode_cvode_io$(PreprocessSuffix) "src/libs/cvode/cvode_io.c"

$(IntermediateDirectory)/cvode_cvode_spbcgs$(ObjectSuffix): src/libs/cvode/cvode_spbcgs.c $(IntermediateDirectory)/cvode_cvode_spbcgs$(DependSuffix)
	$(CC) $(SourceSwitch) "./src/libs/cvode/cvode_spbcgs.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cvode_cvode_spbcgs$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cvode_cvode_spbcgs$(DependSuffix): src/libs/cvode/cvode_spbcgs.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cvode_cvode_spbcgs$(ObjectSuffix) -MF$(IntermediateDirectory)/cvode_cvode_spbcgs$(DependSuffix) -MM "src/libs/cvode/cvode_spbcgs.c"

$(IntermediateDirectory)/cvode_cvode_spbcgs$(PreprocessSuffix): src/libs/cvode/cvode_spbcgs.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cvode_cvode_spbcgs$(PreprocessSuffix) "src/libs/cvode/cvode_spbcgs.c"

$(IntermediateDirectory)/cvode_cvode_spgmr$(ObjectSuffix): src/libs/cvode/cvode_spgmr.c $(IntermediateDirectory)/cvode_cvode_spgmr$(DependSuffix)
	$(CC) $(SourceSwitch) "./src/libs/cvode/cvode_spgmr.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cvode_cvode_spgmr$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cvode_cvode_spgmr$(DependSuffix): src/libs/cvode/cvode_spgmr.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cvode_cvode_spgmr$(ObjectSuffix) -MF$(IntermediateDirectory)/cvode_cvode_spgmr$(DependSuffix) -MM "src/libs/cvode/cvode_spgmr.c"

$(IntermediateDirectory)/cvode_cvode_spgmr$(PreprocessSuffix): src/libs/cvode/cvode_spgmr.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cvode_cvode_spgmr$(PreprocessSuffix) "src/libs/cvode/cvode_spgmr.c"

$(IntermediateDirectory)/cvode_cvode_spils$(ObjectSuffix): src/libs/cvode/cvode_spils.c $(IntermediateDirectory)/cvode_cvode_spils$(DependSuffix)
	$(CC) $(SourceSwitch) "./src/libs/cvode/cvode_spils.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cvode_cvode_spils$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cvode_cvode_spils$(DependSuffix): src/libs/cvode/cvode_spils.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cvode_cvode_spils$(ObjectSuffix) -MF$(IntermediateDirectory)/cvode_cvode_spils$(DependSuffix) -MM "src/libs/cvode/cvode_spils.c"

$(IntermediateDirectory)/cvode_cvode_spils$(PreprocessSuffix): src/libs/cvode/cvode_spils.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cvode_cvode_spils$(PreprocessSuffix) "src/libs/cvode/cvode_spils.c"

$(IntermediateDirectory)/cvode_cvode_sptfqmr$(ObjectSuffix): src/libs/cvode/cvode_sptfqmr.c $(IntermediateDirectory)/cvode_cvode_sptfqmr$(DependSuffix)
	$(CC) $(SourceSwitch) "./src/libs/cvode/cvode_sptfqmr.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cvode_cvode_sptfqmr$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cvode_cvode_sptfqmr$(DependSuffix): src/libs/cvode/cvode_sptfqmr.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cvode_cvode_sptfqmr$(ObjectSuffix) -MF$(IntermediateDirectory)/cvode_cvode_sptfqmr$(DependSuffix) -MM "src/libs/cvode/cvode_sptfqmr.c"

$(IntermediateDirectory)/cvode_cvode_sptfqmr$(PreprocessSuffix): src/libs/cvode/cvode_sptfqmr.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cvode_cvode_sptfqmr$(PreprocessSuffix) "src/libs/cvode/cvode_sptfqmr.c"

$(IntermediateDirectory)/nvec_ser_fnvector_serial$(ObjectSuffix): src/libs/nvec_ser/fnvector_serial.c $(IntermediateDirectory)/nvec_ser_fnvector_serial$(DependSuffix)
	$(CC) $(SourceSwitch) "./src/libs/nvec_ser/fnvector_serial.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/nvec_ser_fnvector_serial$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nvec_ser_fnvector_serial$(DependSuffix): src/libs/nvec_ser/fnvector_serial.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/nvec_ser_fnvector_serial$(ObjectSuffix) -MF$(IntermediateDirectory)/nvec_ser_fnvector_serial$(DependSuffix) -MM "src/libs/nvec_ser/fnvector_serial.c"

$(IntermediateDirectory)/nvec_ser_fnvector_serial$(PreprocessSuffix): src/libs/nvec_ser/fnvector_serial.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/nvec_ser_fnvector_serial$(PreprocessSuffix) "src/libs/nvec_ser/fnvector_serial.c"

$(IntermediateDirectory)/nvec_ser_nvector_serial$(ObjectSuffix): src/libs/nvec_ser/nvector_serial.c $(IntermediateDirectory)/nvec_ser_nvector_serial$(DependSuffix)
	$(CC) $(SourceSwitch) "./src/libs/nvec_ser/nvector_serial.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/nvec_ser_nvector_serial$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/nvec_ser_nvector_serial$(DependSuffix): src/libs/nvec_ser/nvector_serial.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/nvec_ser_nvector_serial$(ObjectSuffix) -MF$(IntermediateDirectory)/nvec_ser_nvector_serial$(DependSuffix) -MM "src/libs/nvec_ser/nvector_serial.c"

$(IntermediateDirectory)/nvec_ser_nvector_serial$(PreprocessSuffix): src/libs/nvec_ser/nvector_serial.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/nvec_ser_nvector_serial$(PreprocessSuffix) "src/libs/nvec_ser/nvector_serial.c"

$(IntermediateDirectory)/sundials_sundials_band$(ObjectSuffix): src/libs/sundials/sundials_band.c $(IntermediateDirectory)/sundials_sundials_band$(DependSuffix)
	$(CC) $(SourceSwitch) "./src/libs/sundials/sundials_band.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sundials_sundials_band$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sundials_sundials_band$(DependSuffix): src/libs/sundials/sundials_band.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sundials_sundials_band$(ObjectSuffix) -MF$(IntermediateDirectory)/sundials_sundials_band$(DependSuffix) -MM "src/libs/sundials/sundials_band.c"

$(IntermediateDirectory)/sundials_sundials_band$(PreprocessSuffix): src/libs/sundials/sundials_band.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sundials_sundials_band$(PreprocessSuffix) "src/libs/sundials/sundials_band.c"

$(IntermediateDirectory)/sundials_sundials_dense$(ObjectSuffix): src/libs/sundials/sundials_dense.c $(IntermediateDirectory)/sundials_sundials_dense$(DependSuffix)
	$(CC) $(SourceSwitch) "./src/libs/sundials/sundials_dense.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sundials_sundials_dense$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sundials_sundials_dense$(DependSuffix): src/libs/sundials/sundials_dense.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sundials_sundials_dense$(ObjectSuffix) -MF$(IntermediateDirectory)/sundials_sundials_dense$(DependSuffix) -MM "src/libs/sundials/sundials_dense.c"

$(IntermediateDirectory)/sundials_sundials_dense$(PreprocessSuffix): src/libs/sundials/sundials_dense.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sundials_sundials_dense$(PreprocessSuffix) "src/libs/sundials/sundials_dense.c"

$(IntermediateDirectory)/sundials_sundials_direct$(ObjectSuffix): src/libs/sundials/sundials_direct.c $(IntermediateDirectory)/sundials_sundials_direct$(DependSuffix)
	$(CC) $(SourceSwitch) "./src/libs/sundials/sundials_direct.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sundials_sundials_direct$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sundials_sundials_direct$(DependSuffix): src/libs/sundials/sundials_direct.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sundials_sundials_direct$(ObjectSuffix) -MF$(IntermediateDirectory)/sundials_sundials_direct$(DependSuffix) -MM "src/libs/sundials/sundials_direct.c"

$(IntermediateDirectory)/sundials_sundials_direct$(PreprocessSuffix): src/libs/sundials/sundials_direct.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sundials_sundials_direct$(PreprocessSuffix) "src/libs/sundials/sundials_direct.c"

$(IntermediateDirectory)/sundials_sundials_iterative$(ObjectSuffix): src/libs/sundials/sundials_iterative.c $(IntermediateDirectory)/sundials_sundials_iterative$(DependSuffix)
	$(CC) $(SourceSwitch) "./src/libs/sundials/sundials_iterative.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sundials_sundials_iterative$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sundials_sundials_iterative$(DependSuffix): src/libs/sundials/sundials_iterative.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sundials_sundials_iterative$(ObjectSuffix) -MF$(IntermediateDirectory)/sundials_sundials_iterative$(DependSuffix) -MM "src/libs/sundials/sundials_iterative.c"

$(IntermediateDirectory)/sundials_sundials_iterative$(PreprocessSuffix): src/libs/sundials/sundials_iterative.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sundials_sundials_iterative$(PreprocessSuffix) "src/libs/sundials/sundials_iterative.c"

$(IntermediateDirectory)/sundials_sundials_math$(ObjectSuffix): src/libs/sundials/sundials_math.c $(IntermediateDirectory)/sundials_sundials_math$(DependSuffix)
	$(CC) $(SourceSwitch) "./src/libs/sundials/sundials_math.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sundials_sundials_math$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sundials_sundials_math$(DependSuffix): src/libs/sundials/sundials_math.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sundials_sundials_math$(ObjectSuffix) -MF$(IntermediateDirectory)/sundials_sundials_math$(DependSuffix) -MM "src/libs/sundials/sundials_math.c"

$(IntermediateDirectory)/sundials_sundials_math$(PreprocessSuffix): src/libs/sundials/sundials_math.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sundials_sundials_math$(PreprocessSuffix) "src/libs/sundials/sundials_math.c"

$(IntermediateDirectory)/sundials_sundials_nvector$(ObjectSuffix): src/libs/sundials/sundials_nvector.c $(IntermediateDirectory)/sundials_sundials_nvector$(DependSuffix)
	$(CC) $(SourceSwitch) "./src/libs/sundials/sundials_nvector.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sundials_sundials_nvector$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sundials_sundials_nvector$(DependSuffix): src/libs/sundials/sundials_nvector.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sundials_sundials_nvector$(ObjectSuffix) -MF$(IntermediateDirectory)/sundials_sundials_nvector$(DependSuffix) -MM "src/libs/sundials/sundials_nvector.c"

$(IntermediateDirectory)/sundials_sundials_nvector$(PreprocessSuffix): src/libs/sundials/sundials_nvector.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sundials_sundials_nvector$(PreprocessSuffix) "src/libs/sundials/sundials_nvector.c"

$(IntermediateDirectory)/sundials_sundials_spbcgs$(ObjectSuffix): src/libs/sundials/sundials_spbcgs.c $(IntermediateDirectory)/sundials_sundials_spbcgs$(DependSuffix)
	$(CC) $(SourceSwitch) "./src/libs/sundials/sundials_spbcgs.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sundials_sundials_spbcgs$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sundials_sundials_spbcgs$(DependSuffix): src/libs/sundials/sundials_spbcgs.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sundials_sundials_spbcgs$(ObjectSuffix) -MF$(IntermediateDirectory)/sundials_sundials_spbcgs$(DependSuffix) -MM "src/libs/sundials/sundials_spbcgs.c"

$(IntermediateDirectory)/sundials_sundials_spbcgs$(PreprocessSuffix): src/libs/sundials/sundials_spbcgs.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sundials_sundials_spbcgs$(PreprocessSuffix) "src/libs/sundials/sundials_spbcgs.c"

$(IntermediateDirectory)/sundials_sundials_spgmr$(ObjectSuffix): src/libs/sundials/sundials_spgmr.c $(IntermediateDirectory)/sundials_sundials_spgmr$(DependSuffix)
	$(CC) $(SourceSwitch) "./src/libs/sundials/sundials_spgmr.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sundials_sundials_spgmr$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sundials_sundials_spgmr$(DependSuffix): src/libs/sundials/sundials_spgmr.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sundials_sundials_spgmr$(ObjectSuffix) -MF$(IntermediateDirectory)/sundials_sundials_spgmr$(DependSuffix) -MM "src/libs/sundials/sundials_spgmr.c"

$(IntermediateDirectory)/sundials_sundials_spgmr$(PreprocessSuffix): src/libs/sundials/sundials_spgmr.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sundials_sundials_spgmr$(PreprocessSuffix) "src/libs/sundials/sundials_spgmr.c"

$(IntermediateDirectory)/sundials_sundials_sptfqmr$(ObjectSuffix): src/libs/sundials/sundials_sptfqmr.c $(IntermediateDirectory)/sundials_sundials_sptfqmr$(DependSuffix)
	$(CC) $(SourceSwitch) "./src/libs/sundials/sundials_sptfqmr.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sundials_sundials_sptfqmr$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sundials_sundials_sptfqmr$(DependSuffix): src/libs/sundials/sundials_sptfqmr.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sundials_sundials_sptfqmr$(ObjectSuffix) -MF$(IntermediateDirectory)/sundials_sundials_sptfqmr$(DependSuffix) -MM "src/libs/sundials/sundials_sptfqmr.c"

$(IntermediateDirectory)/sundials_sundials_sptfqmr$(PreprocessSuffix): src/libs/sundials/sundials_sptfqmr.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sundials_sundials_sptfqmr$(PreprocessSuffix) "src/libs/sundials/sundials_sptfqmr.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/src_MRG_init$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_MRG_init$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_MRG_init$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_MRG_main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_MRG_main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_MRG_main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_MRG_ode$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_MRG_ode$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_MRG_ode$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_utils$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_utils$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_utils$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode$(DependSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_band$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_band$(DependSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_band$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_bandpre$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_bandpre$(DependSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_bandpre$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_bbdpre$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_bbdpre$(DependSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_bbdpre$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_dense$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_dense$(DependSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_dense$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_diag$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_diag$(DependSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_diag$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_direct$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_direct$(DependSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_direct$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_io$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_io$(DependSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_io$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_spbcgs$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_spbcgs$(DependSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_spbcgs$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_spgmr$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_spgmr$(DependSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_spgmr$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_spils$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_spils$(DependSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_spils$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_sptfqmr$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_sptfqmr$(DependSuffix)
	$(RM) $(IntermediateDirectory)/cvode_cvode_sptfqmr$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nvec_ser_fnvector_serial$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nvec_ser_fnvector_serial$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nvec_ser_fnvector_serial$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/nvec_ser_nvector_serial$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/nvec_ser_nvector_serial$(DependSuffix)
	$(RM) $(IntermediateDirectory)/nvec_ser_nvector_serial$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/sundials_sundials_band$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/sundials_sundials_band$(DependSuffix)
	$(RM) $(IntermediateDirectory)/sundials_sundials_band$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/sundials_sundials_dense$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/sundials_sundials_dense$(DependSuffix)
	$(RM) $(IntermediateDirectory)/sundials_sundials_dense$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/sundials_sundials_direct$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/sundials_sundials_direct$(DependSuffix)
	$(RM) $(IntermediateDirectory)/sundials_sundials_direct$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/sundials_sundials_iterative$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/sundials_sundials_iterative$(DependSuffix)
	$(RM) $(IntermediateDirectory)/sundials_sundials_iterative$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/sundials_sundials_math$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/sundials_sundials_math$(DependSuffix)
	$(RM) $(IntermediateDirectory)/sundials_sundials_math$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/sundials_sundials_nvector$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/sundials_sundials_nvector$(DependSuffix)
	$(RM) $(IntermediateDirectory)/sundials_sundials_nvector$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/sundials_sundials_spbcgs$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/sundials_sundials_spbcgs$(DependSuffix)
	$(RM) $(IntermediateDirectory)/sundials_sundials_spbcgs$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/sundials_sundials_spgmr$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/sundials_sundials_spgmr$(DependSuffix)
	$(RM) $(IntermediateDirectory)/sundials_sundials_spgmr$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/sundials_sundials_sptfqmr$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/sundials_sundials_sptfqmr$(DependSuffix)
	$(RM) $(IntermediateDirectory)/sundials_sundials_sptfqmr$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile).exe
	$(RM) ".build-release/mrg_axon_model"


