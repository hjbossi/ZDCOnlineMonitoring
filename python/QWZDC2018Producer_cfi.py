import FWCore.ParameterSet.Config as cms

from HeavyIonsAnalysis.ZDCAnalysis.ZDC2018Pedestal_cfg import ZDC2018Pedestal_0,ZDC2018Pedestal_run326537


zdcdigi = cms.EDProducer('QWZDC2018Producer',
		Src = cms.untracked.InputTag('hcalDigis', 'ZDC'),
		SOI = cms.untracked.int32(3),
		Pedestal = ZDC2018Pedestal_run326537,
		HardCode = cms.untracked.bool(True),
		Debug = cms.untracked.bool(False)
		)

