#-------------------------------------
#	Hcal DQM Application using New DQM Sources/Clients
#	Description: For Local Use(a la DetDiag)
#-------------------------------------

#-------------------------------------
#	Standard Python Imports
#-------------------------------------
import os, sys, socket, string

#-------------------------------------
#	Input Options
#-------------------------------------
import FWCore.ParameterSet.VarParsing as VarParsing
options = VarParsing.VarParsing()

options.register(
	'inputFiles',
	"root://eoscms.cern.ch//eos/cms/store/group/dpg_hcal/comm_hcal/LS1/USC_248441.root", #default
	VarParsing.VarParsing.multiplicity.list,
	VarParsing.VarParsing.varType.string,
	"Input Files"
)

options.register(
	'processEvents',
	-1,
	VarParsing.VarParsing.multiplicity.singleton,
	VarParsing.VarParsing.varType.int,
	"Number of Events to process"
)

options.register(
	'runType',
	'UNKNOWN',
	VarParsing.VarParsing.multiplicity.singleton,
	VarParsing.VarParsing.varType.string,
	"Local Run Type: pedestal, led, laser, raddam"
)

options.register(
	'harvestRunList',
	[],
	VarParsing.VarParsing.multiplicity.list,
	VarParsing.VarParsing.varType.int,
	"Run List to Harvest"
)

options.parseArguments()

#-------------------------------------
#	Standard CMSSW Imports/Definitions
#-------------------------------------
import FWCore.ParameterSet.Config as cms
from Configuration.StandardSequences.Eras import eras
process			= cms.Process('HCALDQM', eras.Run3)
subsystem		= 'Hcal'
cmssw			= os.getenv("CMSSW_VERSION").split("_")
debugstr		= "### HcalDQM::cfg::DEBUG: "
warnstr			= "### HcalDQM::cfg::WARN: "
errorstr		= "### HcalDQM::cfg::ERROR:"
local			= True
useMap			= True
dbMap			= False
cmsnet			= False

print(debugstr, "Input Files= ", options.inputFiles)
print(debugstr, "Run over #events=", options.processEvents)


#-------------------------------------
#	Central DQM Stuff imports
#-------------------------------------
if local:
	process.source = cms.Source("HcalTBSource",
                        firstLuminosityBlockForEachRun = cms.untracked.VLuminosityBlockID([]),
		fileNames = cms.untracked.vstring(options.inputFiles)
                )
	process.maxEvents = cms.untracked.PSet(
			input = cms.untracked.int32(options.processEvents)
	)
else:
	print(errorstr + "There is an error with the Source. Exiting...")
	sys.exit(1)
process.load('DQMServices.Components.DQMEnvironment_cfi')
process.load('DQMServices.Core.DQMStore_cfi')

#-------------------------------------
#	DQM Customization
#-------------------------------------
process.DQM = cms.Service(
	"DQM",
	debug = cms.untracked.bool(False),
	publishFrequency = cms.untracked.double(1.0),
	collectorPort = cms.untracked.int32(9999),
	collectorHost = cms.untracked.string('hcaldqm03.cms'),
	filter = cms.untracked.string('')
)
process.dqmSaver.convention = 'Offline'
process.dqmSaver.workflow = "/%s/LOCAL/DQMIO" % options.runType.upper()
process.dqmSaver.referenceHandling = 'all'
process.dqmSaver.dirName = './'
process.dqmSaver.producer = 'DQM'
process.dqmSaver.saveByLumiSection = -1
process.dqmSaver.saveByRun = 1
process.dqmSaver.saveAtJobEnd = False
process.DQMStore.verbose = 1
process.dqmEnv.subSystemFolder = subsystem


#-------------------------------------
#	CMSSW/Hcal non-DQM Related Module import
#-------------------------------------
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('FWCore.MessageLogger.MessageLogger_cfi')
process.load("EventFilter.HcalRawToDigi.HcalRawToDigi_cfi")
process.hcalDigis.InputLabel =  cms.InputTag('source')
#process.load('CondCore.CondDB.CondDB_cfi')
#from Configuration.AlCa.autoCond import autoCond
process.load("SimCalorimetry.HcalTrigPrimProducers.hcaltpdigi_cff")
from Configuration.Applications.ConfigBuilder import MassReplaceInputTag
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '132X_dataRun3_Prompt_v4', '')


#-------------------------------------
#	CMSSW/Hcal non-DQM Related Module Settings
#	-> GlobalTag
#	-> Generic Input tag for the Raw Collection
#	-> cmssw version
#	-> Turn off default blocking of dead channels from rechit collection
#	-> Drop Channel Status Bits (had benn 'HcalCellOff', "HcalCellDead")
#	-> For Trigger Primitives
#	-> L1 GT setting
#	-> Rename the hbheprereco to hbhereco
#-------------------------------------
#process.GlobalTag.globaltag = autoCond['run3_hlt']
if cmsnet:
        process.GlobalTag.connect   = 'frontier://FrontierProd/CMS_CONDITIONS'
	#process.GlobalTag.connect = 'frontier://(serverurl=http://frontier1.cms:8000/FrontierOnProd)(serverurl=http://frontier2.cms:8000/FrontierOnProd)(retrieve-ziplevel=0)/CMS_CONDITIONS'
cmssw			= os.getenv("CMSSW_VERSION").split("_")
rawTagStr		= "source"
rawTag			= cms.InputTag(rawTagStr)
process.MessageLogger.cerr.FwkReport.reportEvery = 1

#-------------------------------------
#	Hcal DQM Tasks and Clients import
#-------------------------------------
process.load('DQM.HcalTasks.RawTask')
process.load("DQM.HcalTasks.PedestalTask")
process.load("DQM.HcalTasks.LEDTask")
process.load("DQM.HcalTasks.LaserTask")
process.load("DQM.HcalTasks.HFRaddamTask")
process.load('DQM.HcalTasks.QIE10Task')
process.load('DQM.HcalTasks.ZDCQIE10Task')
process.load('DQM.HcalTasks.QIE11Task')
process.load('DQM.HcalTasks.DigiTask')
process.load('DQM.HcalTasks.TPTask')
#process.load('DQM.SpecificHarvesting.PedestalHarvesting')
#process.load('DQM.SpecificHarvesting.LEDHarvesting')
#process.load('DQM.SpecificHarvesting.LaserHarvesting')

#-------------------------------------
#	To force using uTCA
#	Will not be here for Online DQM
#-------------------------------------
if useMap==True and dbMap==True:
	process.GlobalTag.toGet.append(cms.PSet(
			record = cms.string("HcalElectronicsMapRcd"),
			tag = cms.string(''),
			)
		 )
elif useMap==True and dbMap==False:
	process.es_ascii = cms.ESSource(
		'HcalTextCalibrations',
		input = cms.VPSet(
			cms.PSet(
				object = cms.string('ElectronicsMap'),
				file = cms.FileInPath("emap_2023_newZDC.txt")
			)
		)
	)
	process.es_prefer = cms.ESPrefer('HcalTextCalibrations', 'es_ascii')

#-------------------------------------
#	To have vme Digis as a separate collection
#-------------------------------------
'''
process.hcalDigis.FEDs = cms.untracked.vint32(724,  725,  726,  727,  728,  729,  730,  731,  1100, 1101, 1102, 1103, 1104, 1105, 1106, 1107, 1108,
                                              1109, 1110, 1111, 1112, 1113, 1114, 1115, 1116, 1117, 1118, 1119, 1120, 1121, 1122, 1123, 1124, 1125,
                                              1126, 1127, 1128, 1129, 1134, 1135, 1140, 1141, 1142, 1143, 1144, 1145, 1146, 1147, 1148)
'''
process.utcaDigis = process.hcalDigis.clone()
process.utcaDigis.InputLabel = rawTag
process.utcaDigis.FEDs = cms.untracked.vint32(1100, 1101, 1102, 1103, 1104, 1105, 1106, 1107, 1108, 1109, 1110,
                                              1111, 1112, 1113, 1114, 1115, 1116, 1117, 1118, 1119, 1120, 1121,
                                              1122, 1123, 1124, 1125, 1126, 1127, 1128, 1129, 1134, 1135, 1140,
                                              1141, 1142, 1143, 1144, 1145, 1146, 1147, 1148)

#-------------------------------------
#	Sequences Definition
#-------------------------------------
shouldHarvest = False
print(options.harvestRunList)
if "pedestal" in options.runType.lower():
	process.tasksSequence = cms.Sequence(
              #  process.rawTask
#		*process.pedestalTask
		#*process.qie10Task
		#*process.qie11Task
               # *process.digiTask
                process.zdcqie10Task
                #*process.tpTask
	)
elif 'led' in options.runType.lower():
	process.tasksSequence = cms.Sequence(
                process.rawTask
		*process.ledTask
		*process.qie10Task
		*process.qie11Task
                *process.digiTask
                *process.tpTask
	)
elif "laser" in options.runType.lower():
	process.tasksSequence = cms.Sequence(
                process.rawTask
		*process.laserTask
		*process.qie10Task
		*process.qie11Task
                *process.digiTask
                *process.tpTask
	)
elif "raddam" in options.runType.lower():
	process.tasksSequence = cms.Sequence(process.hfRaddamTask)
else:
	print("### Exiting. Wrong Run Type: " + options.runType.lower())
	sys.exit(0)

#-------------------------------------
#	Some Settings for Local(a la DetDiag)
#	All Modules are muted by default
#	isGlobal must be set to False!
#	Get the Local Trigger Information	
#-------------------------------------
process.hcalDigis.InputLabel = rawTag
process.pedestalTask.tagRaw = cms.untracked.InputTag('source')
process.laserTask.tagRaw = cms.untracked.InputTag('source')
process.ledTask.tagRaw = cms.untracked.InputTag('source')
process.hfRaddamTask.tagRaw = cms.untracked.InputTag("source")
process.pedestalTask.subsystem = cms.untracked.string("Hcal")
process.laserTask.subsystem = cms.untracked.string("Hcal")
process.ledTask.subsystem = cms.untracked.string("Hcal")
process.pedestalTask.ptype = cms.untracked.int32(2)
process.ledTask.ptype = cms.untracked.int32(2)
process.laserTask.ptype = cms.untracked.int32(2)
process.hfRaddamTask.subsystem = cms.untracked.string('Hcal')
process.hfRaddamTask.ptype = cms.untracked.int32(2)
process.qie10Task.tagRaw = cms.untracked.InputTag("source")
process.qie10Task.ptype = cms.untracked.int32(2)
process.qie11Task.tagRaw = cms.untracked.InputTag("source")
process.qie11Task.ptype = cms.untracked.int32(2)
process.digiTask.tagRaw = cms.untracked.InputTag("source")
process.digiTask.ptype = cms.untracked.int32(2)
process.digiTask.subsystem = cms.untracked.string("Hcal")
process.tpTask.tagRaw = cms.untracked.InputTag("source")
process.tpTask.ptype = cms.untracked.int32(2)
process.tpTask.subsystem = cms.untracked.string("Hcal")
process.rawTask.tagFEDs = cms.untracked.InputTag("source")
process.rawTask.ptype = cms.untracked.int32(2)

process.emulTPDigis = \
                process.simHcalTriggerPrimitiveDigis.clone()
process.emulTPDigis.inputLabel = \
                                cms.VInputTag("hcalDigis", 'hcalDigis')
process.emulTPDigis.FrontEndFormatError = \
                                        cms.bool(True)
process.HcalTPGCoderULUT.LUTGenerationMode = cms.bool(False)
process.emulTPDigis.FG_threshold = cms.uint32(2)
process.emulTPDigis.InputTagFEDRaw = rawTag
process.emulTPDigis.upgradeHF = cms.bool(True)
process.emulTPDigis.upgradeHE = cms.bool(True)
process.emulTPDigis.inputLabel = cms.VInputTag("hcalDigis", "hcalDigis")
process.emulTPDigis.inputUpgradeLabel = cms.VInputTag("hcalDigis", "hcalDigis")
# Enable ZS on emulated TPs, to match what is done in data
process.emulTPDigis.RunZS = cms.bool(True)
process.emulTPDigis.ZS_threshold = cms.uint32(0)
process.emulTPDigisNoTDCCut = process.emulTPDigis.clone()
process.emulTPDigisNoTDCCut.ADCThresholdHF = cms.uint32(0)
process.emulTPDigisNoTDCCut.TDCMaskHF = cms.uint64(0xFFFFFFFFFE000000)
process.zdcqie10Task.runkeyName = cms.untracked.string("hi_run")


#-------------------------------------
#	To see Laser Board info and trigger info
#-------------------------------------
process.tbunpacker = cms.EDProducer(
	"HcalTBObjectUnpacker",
	IncludeUnmatchedHits	= cms.untracked.bool(False),
	HcalTriggerFED			= cms.untracked.int32(1)
)
process.tbunpacker.fedRawDataCollectionTag = rawTag

#-------------------------------------
#	Execution Sequence Definition
#-------------------------------------
if shouldHarvest:
	process.p = cms.Path(
	#	process.tbunpacker
		process.hcalDigis
         #       *process.emulTPDigis
          #      *process.emulTPDigisNoTDCCut
		*process.tasksSequence
		#*process.harvestingSequence
                *process.dqmEnv
                *process.dqmSaver
	)
else:
        process.p = cms.Path(
#                process.tbunpacker
                process.hcalDigis
                #*process.emulTPDigis
                #*process.emulTPDigisNoTDCCut
                *process.tasksSequence
                *process.dqmEnv
                *process.dqmSaver
        )

#-------------------------------------
#	Outputs the event Content for Debugging mostly
#-------------------------------------
process.Out = cms.OutputModule(
	"PoolOutputModule",
	fileName = cms.untracked.string("test.root")
)
process.finalize = cms.EndPath(process.Out)

#-------------------------------------
#	Scheduling
#-------------------------------------
process.options = cms.untracked.PSet(
		Rethrow = cms.untracked.vstring(
			"ProductNotFound",
			"TooManyProducts",
			"TooFewProducts"
		)
)
process.options.wantSummary = cms.untracked.bool(False)
