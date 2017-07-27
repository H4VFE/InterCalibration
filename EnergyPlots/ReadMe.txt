These are instructions on how to use MyAnalysis to get energy plots versus X or Y

It is recommended to have MyAnalysis.C and MyAnalysis.h open in emacs or something because there are certain parts of it that need to be hard-coded. 

Open the desired root file. Take note of the run number. 

Edit the MyAnalysis.C file to use the channel associated with the crystal you want to look at (every instance of maximum[VFE#_#] must be correct).

Edit the MyAnalysis.h file to use the run number you are doing (there are two instances of vfe_ecal_tia_run#, and those must be set to the correct run). 

Run the following code:

.L MyAnalysis.C++
(This compiles the code in case changes were made)

MyAnalysis t

t.Loop()

If there were errors in the compilation of the code. MyAnalysis.C may have to be troubleshot. 
In the MyAnalysis.C code, you can change the channel of choice as well as the range of X or Y and the axis of the plot, etc...
