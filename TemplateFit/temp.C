int temp(void)

{
  //  plot->Fit("gaus"); //This proves you can indeed execute a fit macro like this! Nice!                                                                                                                 
  plot->Draw();
  
  float rbot = 1000;
  float rtop = 5000; 
  float constant = 1;                                                                                                                                                                                     
  float mean = 4500;
  float sig = 150;
  float alpha = -100;                                                                                                                                                                                      
  float N = 100;
                                                                                                                                                                                            
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
       
  TF1*f_cb2    = new TF1("f_cb2","crystalball", mean - sig, mean + 3*sig);                                                                                                                                 
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
