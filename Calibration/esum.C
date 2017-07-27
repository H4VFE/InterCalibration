int esum(void)
{

  TH1F*C3 = new TH1F("C3","C3", 100, 1000, 5000); 


  /* // Just C3
  h4->Draw("maximum[VFE3_2]", " X > -3 && X < 7 && Y > -7 && Y < 3 && maximum[VFE3_2] > 1000");
  TF1*fitg = new TF1("fitg","gaus", 3173, 4313);                                                                                                                                                           
  htemp->Fit("fitg","R"); 
  */

  /* // Unscaled                                                                                                                                                                                                          
 TH1F*C3 = new TH1F("C3","C3", 100, 1000, 6000);                                                                                                                                                           
  h4->Draw("maximum[VFE3_1] + maximum[VFE3_2] + maximum[VFE3_3] + maximum[VFE7_3] + maximum[VFE7_2] + maximum[VFE7_1] + maximum[VFE5_3] + maximum[VFE5_2] + maximum[VFE5_1] >> C3", " X > -3 && X < 7 && Y > -7 && Y < 3");                                                                                                                                            
  */

 
   // Scaled
  TH1F*C3 = new TH1F("C3","C3", 100, 0.5, 1.5); 
  h4->Draw("maximum[VFE3_1]/3640 + maximum[VFE3_2]/3480 + maximum[VFE3_3]/3970 + maximum[VFE7_3]/3730 + maximum[VFE7_2]/3700 + maximum[VFE7_1]/4260 + maximum[VFE5_3]/3780 + maximum[VFE5_2]/3400 + maximum[VFE5_1]/3810 >> C3", " X > -3 && X < 7 && Y > -7 && Y < 3");
  
 
  TF1*fitg = new TF1("fitg","gaus", 0.5, 1.5);                                                                                                                                                      
  C3.Fit("fitg","R"); 

  float mean = fitg->GetParameter(1);
  float errmean = fitg->GetParError(1);
  float sig = fitg->GetParameter(2);
  float errsig = fitg->GetParError(2);
  float error =  (sig/mean)* sqrt( pow((errmean/mean),2) + pow((errsig/sig),2)) ;
 
  std::cout << " ~~~~~~~~~~~ " << std::endl;
  std::cout << " Peak  = " <<  mean << "+/-" << errmean  << std::endl;
  std::cout << " Sigma  = " <<  sig << "+/-" << errsig << std::endl;
  std::cout << " sigma/mean  = " <<  sig/mean << "+/-" << error  << std::endl;
  std::cout << " ~~~~~~~~~~~ " << std::endl;



}
