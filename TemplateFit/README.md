The following instructions explain the details of the template and fitting as well as some general notes.

Note: Reconstruction of runs must be done with an updated .cfg file. Old files don't have the branches needed for WF_val and WF_time. Without these, the code will not run properly. 


Check both Analysis.C, Analysis.h, and generating_template.cpp to make sure they have the correctly named inputs and outputs. The versions in this code are for crystal C3, 150 GeV, run 7200. 

Run generating_template.cpp
(Root may complain, but it always completes its function)

Run the following commands in root:

.L Analysis.C++

Analysis t

t.Loop