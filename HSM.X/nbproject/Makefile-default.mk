#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/HSM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/HSM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=TemplateES_Main.c ../shared/TapeSensorService.c ../shared/Motion.c ../CMPE118/src/AD.c ../CMPE118/src/BOARD.c ../CMPE118/src/ES_CheckEvents.c ../CMPE118/src/ES_Framework.c ../CMPE118/src/ES_KeyboardInput.c ../CMPE118/src/ES_PostList.c ../CMPE118/src/ES_Queue.c ../CMPE118/src/ES_TattleTale.c ../CMPE118/src/ES_Timers.c ../CMPE118/src/IO_Ports.c ../CMPE118/src/RC_Servo.c ../CMPE118/src/pwm.c ../CMPE118/src/serial.c ../shared/TrackwireService.c ../shared/BumperService.c HSM.c FollowTapeSSM.c LiftControlSSM.c KillATM6SSM.c ../shared/BeaconService.c BootupSSM.c HuntATM6SSM.c AvoidObstacleSSM.c HuntRenSSM.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/TemplateES_Main.o ${OBJECTDIR}/_ext/819228780/TapeSensorService.o ${OBJECTDIR}/_ext/819228780/Motion.o ${OBJECTDIR}/_ext/417556191/AD.o ${OBJECTDIR}/_ext/417556191/BOARD.o ${OBJECTDIR}/_ext/417556191/ES_CheckEvents.o ${OBJECTDIR}/_ext/417556191/ES_Framework.o ${OBJECTDIR}/_ext/417556191/ES_KeyboardInput.o ${OBJECTDIR}/_ext/417556191/ES_PostList.o ${OBJECTDIR}/_ext/417556191/ES_Queue.o ${OBJECTDIR}/_ext/417556191/ES_TattleTale.o ${OBJECTDIR}/_ext/417556191/ES_Timers.o ${OBJECTDIR}/_ext/417556191/IO_Ports.o ${OBJECTDIR}/_ext/417556191/RC_Servo.o ${OBJECTDIR}/_ext/417556191/pwm.o ${OBJECTDIR}/_ext/417556191/serial.o ${OBJECTDIR}/_ext/819228780/TrackwireService.o ${OBJECTDIR}/_ext/819228780/BumperService.o ${OBJECTDIR}/HSM.o ${OBJECTDIR}/FollowTapeSSM.o ${OBJECTDIR}/LiftControlSSM.o ${OBJECTDIR}/KillATM6SSM.o ${OBJECTDIR}/_ext/819228780/BeaconService.o ${OBJECTDIR}/BootupSSM.o ${OBJECTDIR}/HuntATM6SSM.o ${OBJECTDIR}/AvoidObstacleSSM.o ${OBJECTDIR}/HuntRenSSM.o
POSSIBLE_DEPFILES=${OBJECTDIR}/TemplateES_Main.o.d ${OBJECTDIR}/_ext/819228780/TapeSensorService.o.d ${OBJECTDIR}/_ext/819228780/Motion.o.d ${OBJECTDIR}/_ext/417556191/AD.o.d ${OBJECTDIR}/_ext/417556191/BOARD.o.d ${OBJECTDIR}/_ext/417556191/ES_CheckEvents.o.d ${OBJECTDIR}/_ext/417556191/ES_Framework.o.d ${OBJECTDIR}/_ext/417556191/ES_KeyboardInput.o.d ${OBJECTDIR}/_ext/417556191/ES_PostList.o.d ${OBJECTDIR}/_ext/417556191/ES_Queue.o.d ${OBJECTDIR}/_ext/417556191/ES_TattleTale.o.d ${OBJECTDIR}/_ext/417556191/ES_Timers.o.d ${OBJECTDIR}/_ext/417556191/IO_Ports.o.d ${OBJECTDIR}/_ext/417556191/RC_Servo.o.d ${OBJECTDIR}/_ext/417556191/pwm.o.d ${OBJECTDIR}/_ext/417556191/serial.o.d ${OBJECTDIR}/_ext/819228780/TrackwireService.o.d ${OBJECTDIR}/_ext/819228780/BumperService.o.d ${OBJECTDIR}/HSM.o.d ${OBJECTDIR}/FollowTapeSSM.o.d ${OBJECTDIR}/LiftControlSSM.o.d ${OBJECTDIR}/KillATM6SSM.o.d ${OBJECTDIR}/_ext/819228780/BeaconService.o.d ${OBJECTDIR}/BootupSSM.o.d ${OBJECTDIR}/HuntATM6SSM.o.d ${OBJECTDIR}/AvoidObstacleSSM.o.d ${OBJECTDIR}/HuntRenSSM.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/TemplateES_Main.o ${OBJECTDIR}/_ext/819228780/TapeSensorService.o ${OBJECTDIR}/_ext/819228780/Motion.o ${OBJECTDIR}/_ext/417556191/AD.o ${OBJECTDIR}/_ext/417556191/BOARD.o ${OBJECTDIR}/_ext/417556191/ES_CheckEvents.o ${OBJECTDIR}/_ext/417556191/ES_Framework.o ${OBJECTDIR}/_ext/417556191/ES_KeyboardInput.o ${OBJECTDIR}/_ext/417556191/ES_PostList.o ${OBJECTDIR}/_ext/417556191/ES_Queue.o ${OBJECTDIR}/_ext/417556191/ES_TattleTale.o ${OBJECTDIR}/_ext/417556191/ES_Timers.o ${OBJECTDIR}/_ext/417556191/IO_Ports.o ${OBJECTDIR}/_ext/417556191/RC_Servo.o ${OBJECTDIR}/_ext/417556191/pwm.o ${OBJECTDIR}/_ext/417556191/serial.o ${OBJECTDIR}/_ext/819228780/TrackwireService.o ${OBJECTDIR}/_ext/819228780/BumperService.o ${OBJECTDIR}/HSM.o ${OBJECTDIR}/FollowTapeSSM.o ${OBJECTDIR}/LiftControlSSM.o ${OBJECTDIR}/KillATM6SSM.o ${OBJECTDIR}/_ext/819228780/BeaconService.o ${OBJECTDIR}/BootupSSM.o ${OBJECTDIR}/HuntATM6SSM.o ${OBJECTDIR}/AvoidObstacleSSM.o ${OBJECTDIR}/HuntRenSSM.o

# Source Files
SOURCEFILES=TemplateES_Main.c ../shared/TapeSensorService.c ../shared/Motion.c ../CMPE118/src/AD.c ../CMPE118/src/BOARD.c ../CMPE118/src/ES_CheckEvents.c ../CMPE118/src/ES_Framework.c ../CMPE118/src/ES_KeyboardInput.c ../CMPE118/src/ES_PostList.c ../CMPE118/src/ES_Queue.c ../CMPE118/src/ES_TattleTale.c ../CMPE118/src/ES_Timers.c ../CMPE118/src/IO_Ports.c ../CMPE118/src/RC_Servo.c ../CMPE118/src/pwm.c ../CMPE118/src/serial.c ../shared/TrackwireService.c ../shared/BumperService.c HSM.c FollowTapeSSM.c LiftControlSSM.c KillATM6SSM.c ../shared/BeaconService.c BootupSSM.c HuntATM6SSM.c AvoidObstacleSSM.c HuntRenSSM.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

# The following macros may be used in the pre and post step lines
Device=PIC32MX320F128H
ProjectDir="C:\Users\clindqui\Desktop\Code\mech\HSM.X"
ConfName=default
ImagePath="dist\default\${IMAGE_TYPE}\HSM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="dist\default\${IMAGE_TYPE}"
ImageName="HSM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif

.build-conf:  .pre ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/HSM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX320F128H
MP_LINKER_FILE_OPTION=,--script="C:\CMPE118\bootloader320.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/TemplateES_Main.o: TemplateES_Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TemplateES_Main.o.d 
	@${RM} ${OBJECTDIR}/TemplateES_Main.o 
	@${FIXDEPS} "${OBJECTDIR}/TemplateES_Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/TemplateES_Main.o.d" -o ${OBJECTDIR}/TemplateES_Main.o TemplateES_Main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/819228780/TapeSensorService.o: ../shared/TapeSensorService.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/819228780" 
	@${RM} ${OBJECTDIR}/_ext/819228780/TapeSensorService.o.d 
	@${RM} ${OBJECTDIR}/_ext/819228780/TapeSensorService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/819228780/TapeSensorService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/819228780/TapeSensorService.o.d" -o ${OBJECTDIR}/_ext/819228780/TapeSensorService.o ../shared/TapeSensorService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/819228780/Motion.o: ../shared/Motion.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/819228780" 
	@${RM} ${OBJECTDIR}/_ext/819228780/Motion.o.d 
	@${RM} ${OBJECTDIR}/_ext/819228780/Motion.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/819228780/Motion.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/819228780/Motion.o.d" -o ${OBJECTDIR}/_ext/819228780/Motion.o ../shared/Motion.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/417556191/AD.o: ../CMPE118/src/AD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/417556191" 
	@${RM} ${OBJECTDIR}/_ext/417556191/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/417556191/AD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/417556191/AD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/417556191/AD.o.d" -o ${OBJECTDIR}/_ext/417556191/AD.o ../CMPE118/src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/417556191/BOARD.o: ../CMPE118/src/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/417556191" 
	@${RM} ${OBJECTDIR}/_ext/417556191/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/417556191/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/417556191/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/417556191/BOARD.o.d" -o ${OBJECTDIR}/_ext/417556191/BOARD.o ../CMPE118/src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/417556191/ES_CheckEvents.o: ../CMPE118/src/ES_CheckEvents.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/417556191" 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_CheckEvents.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/417556191/ES_CheckEvents.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/417556191/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/417556191/ES_CheckEvents.o ../CMPE118/src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/417556191/ES_Framework.o: ../CMPE118/src/ES_Framework.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/417556191" 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_Framework.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/417556191/ES_Framework.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/417556191/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/417556191/ES_Framework.o ../CMPE118/src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/417556191/ES_KeyboardInput.o: ../CMPE118/src/ES_KeyboardInput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/417556191" 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_KeyboardInput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/417556191/ES_KeyboardInput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/417556191/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/417556191/ES_KeyboardInput.o ../CMPE118/src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/417556191/ES_PostList.o: ../CMPE118/src/ES_PostList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/417556191" 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_PostList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/417556191/ES_PostList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/417556191/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/417556191/ES_PostList.o ../CMPE118/src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/417556191/ES_Queue.o: ../CMPE118/src/ES_Queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/417556191" 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_Queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/417556191/ES_Queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/417556191/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/417556191/ES_Queue.o ../CMPE118/src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/417556191/ES_TattleTale.o: ../CMPE118/src/ES_TattleTale.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/417556191" 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_TattleTale.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/417556191/ES_TattleTale.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/417556191/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/417556191/ES_TattleTale.o ../CMPE118/src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/417556191/ES_Timers.o: ../CMPE118/src/ES_Timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/417556191" 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_Timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/417556191/ES_Timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/417556191/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/417556191/ES_Timers.o ../CMPE118/src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/417556191/IO_Ports.o: ../CMPE118/src/IO_Ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/417556191" 
	@${RM} ${OBJECTDIR}/_ext/417556191/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/417556191/IO_Ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/417556191/IO_Ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/417556191/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/417556191/IO_Ports.o ../CMPE118/src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/417556191/RC_Servo.o: ../CMPE118/src/RC_Servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/417556191" 
	@${RM} ${OBJECTDIR}/_ext/417556191/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/417556191/RC_Servo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/417556191/RC_Servo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/417556191/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/417556191/RC_Servo.o ../CMPE118/src/RC_Servo.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/417556191/pwm.o: ../CMPE118/src/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/417556191" 
	@${RM} ${OBJECTDIR}/_ext/417556191/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/417556191/pwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/417556191/pwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/417556191/pwm.o.d" -o ${OBJECTDIR}/_ext/417556191/pwm.o ../CMPE118/src/pwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/417556191/serial.o: ../CMPE118/src/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/417556191" 
	@${RM} ${OBJECTDIR}/_ext/417556191/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/417556191/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/417556191/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/417556191/serial.o.d" -o ${OBJECTDIR}/_ext/417556191/serial.o ../CMPE118/src/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/819228780/TrackwireService.o: ../shared/TrackwireService.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/819228780" 
	@${RM} ${OBJECTDIR}/_ext/819228780/TrackwireService.o.d 
	@${RM} ${OBJECTDIR}/_ext/819228780/TrackwireService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/819228780/TrackwireService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/819228780/TrackwireService.o.d" -o ${OBJECTDIR}/_ext/819228780/TrackwireService.o ../shared/TrackwireService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/819228780/BumperService.o: ../shared/BumperService.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/819228780" 
	@${RM} ${OBJECTDIR}/_ext/819228780/BumperService.o.d 
	@${RM} ${OBJECTDIR}/_ext/819228780/BumperService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/819228780/BumperService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/819228780/BumperService.o.d" -o ${OBJECTDIR}/_ext/819228780/BumperService.o ../shared/BumperService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/HSM.o: HSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/HSM.o.d 
	@${RM} ${OBJECTDIR}/HSM.o 
	@${FIXDEPS} "${OBJECTDIR}/HSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/HSM.o.d" -o ${OBJECTDIR}/HSM.o HSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FollowTapeSSM.o: FollowTapeSSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FollowTapeSSM.o.d 
	@${RM} ${OBJECTDIR}/FollowTapeSSM.o 
	@${FIXDEPS} "${OBJECTDIR}/FollowTapeSSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/FollowTapeSSM.o.d" -o ${OBJECTDIR}/FollowTapeSSM.o FollowTapeSSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/LiftControlSSM.o: LiftControlSSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LiftControlSSM.o.d 
	@${RM} ${OBJECTDIR}/LiftControlSSM.o 
	@${FIXDEPS} "${OBJECTDIR}/LiftControlSSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/LiftControlSSM.o.d" -o ${OBJECTDIR}/LiftControlSSM.o LiftControlSSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/KillATM6SSM.o: KillATM6SSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/KillATM6SSM.o.d 
	@${RM} ${OBJECTDIR}/KillATM6SSM.o 
	@${FIXDEPS} "${OBJECTDIR}/KillATM6SSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/KillATM6SSM.o.d" -o ${OBJECTDIR}/KillATM6SSM.o KillATM6SSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/819228780/BeaconService.o: ../shared/BeaconService.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/819228780" 
	@${RM} ${OBJECTDIR}/_ext/819228780/BeaconService.o.d 
	@${RM} ${OBJECTDIR}/_ext/819228780/BeaconService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/819228780/BeaconService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/819228780/BeaconService.o.d" -o ${OBJECTDIR}/_ext/819228780/BeaconService.o ../shared/BeaconService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/BootupSSM.o: BootupSSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BootupSSM.o.d 
	@${RM} ${OBJECTDIR}/BootupSSM.o 
	@${FIXDEPS} "${OBJECTDIR}/BootupSSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/BootupSSM.o.d" -o ${OBJECTDIR}/BootupSSM.o BootupSSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/HuntATM6SSM.o: HuntATM6SSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/HuntATM6SSM.o.d 
	@${RM} ${OBJECTDIR}/HuntATM6SSM.o 
	@${FIXDEPS} "${OBJECTDIR}/HuntATM6SSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/HuntATM6SSM.o.d" -o ${OBJECTDIR}/HuntATM6SSM.o HuntATM6SSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/AvoidObstacleSSM.o: AvoidObstacleSSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/AvoidObstacleSSM.o.d 
	@${RM} ${OBJECTDIR}/AvoidObstacleSSM.o 
	@${FIXDEPS} "${OBJECTDIR}/AvoidObstacleSSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/AvoidObstacleSSM.o.d" -o ${OBJECTDIR}/AvoidObstacleSSM.o AvoidObstacleSSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/HuntRenSSM.o: HuntRenSSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/HuntRenSSM.o.d 
	@${RM} ${OBJECTDIR}/HuntRenSSM.o 
	@${FIXDEPS} "${OBJECTDIR}/HuntRenSSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/HuntRenSSM.o.d" -o ${OBJECTDIR}/HuntRenSSM.o HuntRenSSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/TemplateES_Main.o: TemplateES_Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TemplateES_Main.o.d 
	@${RM} ${OBJECTDIR}/TemplateES_Main.o 
	@${FIXDEPS} "${OBJECTDIR}/TemplateES_Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/TemplateES_Main.o.d" -o ${OBJECTDIR}/TemplateES_Main.o TemplateES_Main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/819228780/TapeSensorService.o: ../shared/TapeSensorService.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/819228780" 
	@${RM} ${OBJECTDIR}/_ext/819228780/TapeSensorService.o.d 
	@${RM} ${OBJECTDIR}/_ext/819228780/TapeSensorService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/819228780/TapeSensorService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/819228780/TapeSensorService.o.d" -o ${OBJECTDIR}/_ext/819228780/TapeSensorService.o ../shared/TapeSensorService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/819228780/Motion.o: ../shared/Motion.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/819228780" 
	@${RM} ${OBJECTDIR}/_ext/819228780/Motion.o.d 
	@${RM} ${OBJECTDIR}/_ext/819228780/Motion.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/819228780/Motion.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/819228780/Motion.o.d" -o ${OBJECTDIR}/_ext/819228780/Motion.o ../shared/Motion.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/417556191/AD.o: ../CMPE118/src/AD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/417556191" 
	@${RM} ${OBJECTDIR}/_ext/417556191/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/417556191/AD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/417556191/AD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/417556191/AD.o.d" -o ${OBJECTDIR}/_ext/417556191/AD.o ../CMPE118/src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/417556191/BOARD.o: ../CMPE118/src/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/417556191" 
	@${RM} ${OBJECTDIR}/_ext/417556191/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/417556191/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/417556191/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/417556191/BOARD.o.d" -o ${OBJECTDIR}/_ext/417556191/BOARD.o ../CMPE118/src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/417556191/ES_CheckEvents.o: ../CMPE118/src/ES_CheckEvents.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/417556191" 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_CheckEvents.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/417556191/ES_CheckEvents.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/417556191/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/417556191/ES_CheckEvents.o ../CMPE118/src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/417556191/ES_Framework.o: ../CMPE118/src/ES_Framework.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/417556191" 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_Framework.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/417556191/ES_Framework.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/417556191/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/417556191/ES_Framework.o ../CMPE118/src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/417556191/ES_KeyboardInput.o: ../CMPE118/src/ES_KeyboardInput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/417556191" 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_KeyboardInput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/417556191/ES_KeyboardInput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/417556191/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/417556191/ES_KeyboardInput.o ../CMPE118/src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/417556191/ES_PostList.o: ../CMPE118/src/ES_PostList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/417556191" 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_PostList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/417556191/ES_PostList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/417556191/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/417556191/ES_PostList.o ../CMPE118/src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/417556191/ES_Queue.o: ../CMPE118/src/ES_Queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/417556191" 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_Queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/417556191/ES_Queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/417556191/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/417556191/ES_Queue.o ../CMPE118/src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/417556191/ES_TattleTale.o: ../CMPE118/src/ES_TattleTale.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/417556191" 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_TattleTale.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/417556191/ES_TattleTale.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/417556191/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/417556191/ES_TattleTale.o ../CMPE118/src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/417556191/ES_Timers.o: ../CMPE118/src/ES_Timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/417556191" 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/417556191/ES_Timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/417556191/ES_Timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/417556191/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/417556191/ES_Timers.o ../CMPE118/src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/417556191/IO_Ports.o: ../CMPE118/src/IO_Ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/417556191" 
	@${RM} ${OBJECTDIR}/_ext/417556191/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/417556191/IO_Ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/417556191/IO_Ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/417556191/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/417556191/IO_Ports.o ../CMPE118/src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/417556191/RC_Servo.o: ../CMPE118/src/RC_Servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/417556191" 
	@${RM} ${OBJECTDIR}/_ext/417556191/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/417556191/RC_Servo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/417556191/RC_Servo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/417556191/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/417556191/RC_Servo.o ../CMPE118/src/RC_Servo.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/417556191/pwm.o: ../CMPE118/src/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/417556191" 
	@${RM} ${OBJECTDIR}/_ext/417556191/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/417556191/pwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/417556191/pwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/417556191/pwm.o.d" -o ${OBJECTDIR}/_ext/417556191/pwm.o ../CMPE118/src/pwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/417556191/serial.o: ../CMPE118/src/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/417556191" 
	@${RM} ${OBJECTDIR}/_ext/417556191/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/417556191/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/417556191/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/417556191/serial.o.d" -o ${OBJECTDIR}/_ext/417556191/serial.o ../CMPE118/src/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/819228780/TrackwireService.o: ../shared/TrackwireService.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/819228780" 
	@${RM} ${OBJECTDIR}/_ext/819228780/TrackwireService.o.d 
	@${RM} ${OBJECTDIR}/_ext/819228780/TrackwireService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/819228780/TrackwireService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/819228780/TrackwireService.o.d" -o ${OBJECTDIR}/_ext/819228780/TrackwireService.o ../shared/TrackwireService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/819228780/BumperService.o: ../shared/BumperService.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/819228780" 
	@${RM} ${OBJECTDIR}/_ext/819228780/BumperService.o.d 
	@${RM} ${OBJECTDIR}/_ext/819228780/BumperService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/819228780/BumperService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/819228780/BumperService.o.d" -o ${OBJECTDIR}/_ext/819228780/BumperService.o ../shared/BumperService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/HSM.o: HSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/HSM.o.d 
	@${RM} ${OBJECTDIR}/HSM.o 
	@${FIXDEPS} "${OBJECTDIR}/HSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/HSM.o.d" -o ${OBJECTDIR}/HSM.o HSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FollowTapeSSM.o: FollowTapeSSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FollowTapeSSM.o.d 
	@${RM} ${OBJECTDIR}/FollowTapeSSM.o 
	@${FIXDEPS} "${OBJECTDIR}/FollowTapeSSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/FollowTapeSSM.o.d" -o ${OBJECTDIR}/FollowTapeSSM.o FollowTapeSSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/LiftControlSSM.o: LiftControlSSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LiftControlSSM.o.d 
	@${RM} ${OBJECTDIR}/LiftControlSSM.o 
	@${FIXDEPS} "${OBJECTDIR}/LiftControlSSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/LiftControlSSM.o.d" -o ${OBJECTDIR}/LiftControlSSM.o LiftControlSSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/KillATM6SSM.o: KillATM6SSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/KillATM6SSM.o.d 
	@${RM} ${OBJECTDIR}/KillATM6SSM.o 
	@${FIXDEPS} "${OBJECTDIR}/KillATM6SSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/KillATM6SSM.o.d" -o ${OBJECTDIR}/KillATM6SSM.o KillATM6SSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/819228780/BeaconService.o: ../shared/BeaconService.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/819228780" 
	@${RM} ${OBJECTDIR}/_ext/819228780/BeaconService.o.d 
	@${RM} ${OBJECTDIR}/_ext/819228780/BeaconService.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/819228780/BeaconService.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/_ext/819228780/BeaconService.o.d" -o ${OBJECTDIR}/_ext/819228780/BeaconService.o ../shared/BeaconService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/BootupSSM.o: BootupSSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BootupSSM.o.d 
	@${RM} ${OBJECTDIR}/BootupSSM.o 
	@${FIXDEPS} "${OBJECTDIR}/BootupSSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/BootupSSM.o.d" -o ${OBJECTDIR}/BootupSSM.o BootupSSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/HuntATM6SSM.o: HuntATM6SSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/HuntATM6SSM.o.d 
	@${RM} ${OBJECTDIR}/HuntATM6SSM.o 
	@${FIXDEPS} "${OBJECTDIR}/HuntATM6SSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/HuntATM6SSM.o.d" -o ${OBJECTDIR}/HuntATM6SSM.o HuntATM6SSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/AvoidObstacleSSM.o: AvoidObstacleSSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/AvoidObstacleSSM.o.d 
	@${RM} ${OBJECTDIR}/AvoidObstacleSSM.o 
	@${FIXDEPS} "${OBJECTDIR}/AvoidObstacleSSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/AvoidObstacleSSM.o.d" -o ${OBJECTDIR}/AvoidObstacleSSM.o AvoidObstacleSSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/HuntRenSSM.o: HuntRenSSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/HuntRenSSM.o.d 
	@${RM} ${OBJECTDIR}/HuntRenSSM.o 
	@${FIXDEPS} "${OBJECTDIR}/HuntRenSSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"../shared" -I"../CMPE118/include" -MMD -MF "${OBJECTDIR}/HuntRenSSM.o.d" -o ${OBJECTDIR}/HuntRenSSM.o HuntRenSSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/HSM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    C:/CMPE118/bootloader320.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_SIMULATOR=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/HSM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/HSM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   C:/CMPE118/bootloader320.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/HSM.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/HSM.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif

.pre:
	@echo "--------------------------------------"
	@echo "User defined pre-build step: [python C:\CMPE118\scripts\Enum_To_String.py]"
	@python C:\CMPE118\scripts\Enum_To_String.py
	@echo "--------------------------------------"

# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
