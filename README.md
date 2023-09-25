# ZDCOnlineMonitoring
This contains scripts to run over the 2023 data and plot their results needed for performing the online monitoring of the ZDC. It is divided into two subdirectories (1) python, that contains the run scripts to run over raw data and (2) the plotting macros that plot the results of (1). 

## recHitRAW
This config file in the python folder produces a root file with the ADC and Charge in each channel of the ZDC, it also produces plots related to timing under the fC_vs_BX folder.
To run this file emap_2023_newZDC.txt, QWZDC2018Producer_cfi.py, ZDC2018Pedestal_cfg.py, and all the source files are required.
