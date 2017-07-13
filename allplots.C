int allplots(void)
{

	TCanvas * c1 = new TCanvas("c", "c", 800, 600);
	c1->Divide(5,5);
	c1->SetCanvasSize(1500,1500);

	c1->cd(1);
	gPad->SetLogy();	
	h4->Draw("maximum[VFE8_0]");

	c1->cd(2);
	gPad->SetLogy();	
	h4->Draw("maximum[VFE7_4]");	

	c1->cd(3);			
	gPad->SetLogy();
	h4->Draw("maximum[VFE3_0]");

	c1->cd(4);	
	gPad->SetLogy();
	h4->Draw("maximum[VFE5_4]");

	c1->cd(5);	
	gPad->SetLogy();
	h4->Draw("maximum[VFE4_0]");

	c1->cd(6);	
	gPad->SetLogy();
	h4->Draw("maximum[VFE8_1]");

	c1->cd(7);	
	gPad->SetLogy();
	h4->Draw("maximum[VFE7_3]");	

	c1->cd(8);			
	gPad->SetLogy();
	h4->Draw("maximum[VFE3_1]");

	c1->cd(9);	
	gPad->SetLogy();
	h4->Draw("maximum[VFE5_3]");

	c1->cd(10);	
	gPad->SetLogy();
	h4->Draw("maximum[VFE4_1]");

	c1->cd(11);	
	gPad->SetLogy();
	h4->Draw("maximum[VFE8_2]");

	c1->cd(12);	
	gPad->SetLogy();
	h4->Draw("maximum[VFE7_2]");	

	c1->cd(13);			
	gPad->SetLogy();
	h4->Draw("maximum[VFE3_2]");

	c1->cd(14);	
	gPad->SetLogy();
	h4->Draw("maximum[VFE5_2]");

	c1->cd(15);	
	gPad->SetLogy();
	h4->Draw("maximum[VFE4_2]");

	c1->cd(16);	
	gPad->SetLogy();
	h4->Draw("maximum[VFE8_3]");

	c1->cd(17);	
	gPad->SetLogy();
	h4->Draw("maximum[VFE7_1]");	

	c1->cd(18);			
	gPad->SetLogy();
	h4->Draw("maximum[VFE3_3]");

	c1->cd(19);	
	gPad->SetLogy();
	h4->Draw("maximum[VFE5_1]");

	c1->cd(20);	
	gPad->SetLogy();
	h4->Draw("maximum[VFE4_3]");

	c1->cd(21);	
	gPad->SetLogy();
	h4->Draw("maximum[VFE8_4]");

	c1->cd(22);	
	gPad->SetLogy();
	h4->Draw("maximum[VFE7_0]");	

	c1->cd(23);			
	gPad->SetLogy();
	h4->Draw("maximum[VFE3_4]");

	c1->cd(24);	
	gPad->SetLogy();
	h4->Draw("maximum[VFE5_0]");

	c1->cd(25);	
	gPad->SetLogy();
	h4->Draw("maximum[VFE4_4]");

	c1->SaveAs("namemeplease.png");

}