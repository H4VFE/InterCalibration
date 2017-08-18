int temp(void)

{
  //Crystal Ball fit for an unscaled peak (in the 1000s)
  //  plot->Draw();
  
  /*
  //Unscaled
  float rbot = 500;
  float rtop = 3000;
  float constant = 70;
  float mean = 1800; 
  float sig = 72;
  float alpha = 0.2;
  float N = 6; 
  */


  //Scaled for 150 GeV
  float rbot = 1.6;
  float rtop = 2.5; 
  float constant = 40;
  float mean = 2;
  float sig = 0.03;
  float alpha = 1;
  float N = 6;
  //  */

  /*
  //Scaled for 100 GeV                                                                                                                                                                                     
  float rbot = 0.5;
  float rtop = 1.5;
  float constant = 60;
  float mean = 1.2;
  float sig = 0.02;
  float alpha = 0.3;
  float N = 3;
  //  */

  /*
  //Scaled for 50 GeV
  float rbot = 0.2;
  float rtop = 0.678;
  float constant = 15;
  float mean = 0.5;
  float sig = 0.02;
  float alpha = 0.3;
  float N = 6;
//  */

  /* 
  //Scaled for 20 GeV                                                                                                                                                                                      
  float rbot = 0.05;                                                                                                                                                                                      
  float rtop = 0.25;                                                                                                                                                                                      
  float constant = 15;                                                                                                                                                                                     
  float mean = 0.2;                                                                                                                                                                                        
  float sig = 0.02;                                                                                                                                                                                       
  float alpha = 0.3;                                                                                                                                                                                       
  float N = 6; 
  */
  TF1*f_cb    = new TF1("f_cb","crystalball", rbot, rtop);                                                                                                                                               
  f_cb -> SetParameters(constant, mean, sig, alpha, N);                                                                                                                                                  
  plot->Fit("f_cb","R");                                                                                                                                                                                 

  constant = f_cb->GetParameter(0);                                                                                                                                                                       
  mean = f_cb->GetParameter(1);                                                                                                                                                                            
  float errmean = f_cb->GetParError(1);                                                                                                                                                                   
  sig = f_cb->GetParameter(2);                                                                                                                                                                            
  float errsig = f_cb->GetParError(2);                                                                                                                                                                   
  float error =  (sig/mean)* sqrt( pow((errmean/mean),2) + pow((errsig/sig),2)) ;                                                                                                                       
  alpha = f_cb->GetParameter(3);                                                                                                                                                                          
  N = f_cb->GetParameter(4);                                                                                                                                                                               

  TF1*f_cb2    = new TF1("f_cb2","crystalball", rbot, rtop);
  f_cb2 -> SetParameters(constant,mean,sig,alpha,N);                                                                                                                                                       
  plot->Fit("f_cb2","R");                                                                                                                                                                                  
 
  mean = f_cb2->GetParameter(1);                                                                                                                                                                           
  errmean = f_cb2->GetParError(1);                                                                                                                                                                         
  sig = f_cb2->GetParameter(2);                                                                                                                                                                            
  errsig = f_cb2->GetParError(2);                                                                                                                                                                          
  error =  (sig/mean)* sqrt( pow((errmean/mean),2) + pow((errsig/sig),2)) ;                                                                                                                                
                                                                                                                                                                                                   
  std::cout << " ~~~~~~~~~~~ " << std::endl;                                                                                                                                                              
  std::cout << " Peak  = " <<  mean << "+/-" << errmean  << std::endl;                                                                                                                                    
  std::cout << " Sigma  = " <<  sig << "+/-" << errsig << std::endl;                                                                                                                                      
  std::cout << " sigma/mean  = " <<  sig/mean << "+/-" << error  << std::endl;                                                                                                                            
  std::cout << " ~~~~~~~~~~~ " << std::endl; 


  return 0;
}
