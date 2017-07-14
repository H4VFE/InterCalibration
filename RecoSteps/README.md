The following instructions explain how to reconstruct runs from the test beam:

Start in the lxplus area of H4Analysis and run the following commands:

source scripts/setup.sh

./bin/H4Reco cfg/VFE_adapter_test.cfg run#

The run# chosen should start reconstructing. This can take a while. 

The root file that is created by this process should end up in the ntuples folder. From there, that root file can be copied to a work space outside of the H4Analysis area. 

cp vfe_ecal_tia_run#.root NEWLOCATION

In the new location, the macro ap2.C Can be run on it in root. 
