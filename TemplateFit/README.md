The following instructions explain the details of the template and fitting as well as some general notes.

Note: Reconstruction of runs must be done with an updated .cfg file. Old files don't have the branches needed for WF_val and WF_time. Without these, the code will not run properly. 

The code generating_template.cpp will generate a root file with the name of the format "template_date_CRYS_energy.root" This root file is used in template_fit.cpp. Since the pulse shapes should be the same for the crystals, only one of these files needs to be made. For consistency, B3 at 100 GeV was used. 

After this, template_fit.cpp can be run to create a new root file with workable values for EA_X and EA_Y (weighted X and Y positions based on energy data). 

ESUM.C does an energy sum and plots it. Executed by

.L ESUM.C++
ESUM r
r.Loop

temp.C does a crystal ball fit on the data. 

Note: the template is still being refined. It was noted that the pulse shapes aren't quite the same at different energies. More updates incoming once that is done. 
