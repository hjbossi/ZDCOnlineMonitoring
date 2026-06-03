Tutorial to processing in parallel:

1. cmsenv in CMSSW
2. change RUNTOOLSDIR in makefile to your own runtools path (can be obtained here https://gitlab.cern.ch/cms-hin-pag/ping-high-pt/runtools.git )
3. run makefile
4. Inside run.sh, manually enter the lumisection you want to process in parallel, the input text file (Example.txt in this example) should contains all run folders you want to process. For lumisection, each line would generate a new root file, and inside the brackets "" all the lumisections would be in the same root file.
5. Inside run.sh, match the KEY=${3:-"PhysicsHIForward"} to the labels in input files paths
6. Inside run.sh modify OUTPUTFOLDER=${4:-"/afs/cern.ch/user/x/xirong/ZDCOnlineMonitoring/plotting/output_debug/"} to your own desired outputpath.
7. once the root files are generated, you may have to manually merge those together using hadd before putting the .root output into plottingMacro to plot neutron peaks