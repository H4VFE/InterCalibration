The following instructions explain the details of the template and fitting as well as some general notes.

Note: Reconstruction of runs must be done with an updated .cfg file. Old files don't have the branches needed for WF_val and WF_time. Without these, the code will not run. 

Check both Analysis.C and generating_template.cpp to make sure they have the correctly named inputs and outputs. The versions in this code are for crystal C3, 100 GeV, run 7290. 

Run generating_template.cpp
(Root may complain, but it always completes its function)

Run the following commands in root:
.L Analysis.C++
Analysis t
t.Loop

Notes/Next steps:
Analysis.C needs to be modified to do the 3x3 sum. Currently it does weighted X and Y and plots only C3. 
temp.C can be used after the above commands were executed. This will use a Crystal Ball fit on the histogram plot of template amplitude on a desired range. 
It however, does need some work because the fit isn't quite right. 