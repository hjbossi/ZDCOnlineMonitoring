RunThreeAnalysis is a macro with code that allows you to create time slice distributions, ratios of time slice 2 to time slice 3, fC distributions,
and position weighted signal plots for the RPD and EM. To run the code, you need to read in the data from the root files on your own server. 
The data here is being read in from root files that only exist on the mignerey server
The macro uses heavy ion data from the forest. It uses the TTrees "zdcanalyzer" and "HiTree"
You can make changes to the hibin (centrality) and you can comment out / remove the comments for the canvases
