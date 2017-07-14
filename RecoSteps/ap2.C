int ap2(void)
{

	TCanvas * c1 = new TCanvas("c", "c", 800, 600);
	c1->Divide(5,5);
	c1->SetCanvasSize(2000,2000);

	c1->cd(1);
	TH1F*A1 = new TH1F("A1", "A1", 100, 0, 6000);
	gPad->SetLogy();
	h4->Draw("maximum[VFE8_0] >> A1");

	c1->cd(2);
        TH1F*B1 = new TH1F("B1","B1", 100, 0, 6000);
        gPad->SetLogy();
        h4->Draw("maximum[VFE7_4] >> B1");

	c1->cd(3);
        TH1F*C1 = new TH1F("C1","C1", 100, 0, 6000);
        gPad->SetLogy();
        h4->Draw("maximum[VFE3_0] >> C1");

	c1->cd(4);	
	TH1F*D1 = new TH1F("D1","D1", 100, 0, 6000);
	gPad->SetLogy();
	h4->Draw("maximum[VFE5_4]>>D1");

        c1->cd(5);
	TH1F*E1 = new TH1F("E1","E1", 100, 0, 6000);
        gPad->SetLogy();
	h4->Draw("maximum[VFE4_0]>>E1");

	c1->cd(6);	
	TH1F*A1 = new TH1F("A2","A2", 100, 0, 6000);
       	gPad->SetLogy();
       	h4->Draw("maximum[VFE8_1] >> A2");

       	c1->cd(7);
       	TH1F*B2 = new TH1F("B2","B2", 100, 0, 6000);
       	gPad->SetLogy();
       	h4->Draw("maximum[VFE7_3] >> B2");

       	c1->cd(8);
       	TH1F*C2 = new TH1F("C2","C2", 100, 0, 6000);
       	gPad->SetLogy();
       	h4->Draw("maximum[VFE3_1] >> C2");

       	c1->cd(9);
       	TH1F*D2 = new TH1F("D2","D2", 100, 0, 6000);
       	gPad->SetLogy();
       	h4->Draw("maximum[VFE5_3]>>D2");

        c1->cd(10);
      	TH1F*E2 = new TH1F("E2","E2", 100, 0, 6000);
	gPad->SetLogy();
 	h4->Draw("maximum[VFE4_1]>>E2");

        c1->cd(11);
        TH1F*A3 = new TH1F("A3","A3", 100, 0, 6000);
        gPad->SetLogy();
	h4->Draw("maximum[VFE8_2] >> A3");

        c1->cd(12);
	TH1F*B3 = new TH1F("B3","B3", 100, 0, 6000);
        gPad->SetLogy();
        h4->Draw("maximum[VFE7_2] >> B3");

	c1->cd(13);
        TH1F*C3 = new TH1F("C3","C3", 100, 0, 6000);
        gPad->SetLogy();
        h4->Draw("maximum[VFE3_2] >> C3");

        c1->cd(14);
	TH1F*D3 = new TH1F("D3","D3", 100, 0, 6000);
        gPad->SetLogy();
	h4->Draw("maximum[VFE5_2]>>D3");

        c1->cd(15);
        TH1F*E3 = new TH1F("E3","E3", 100, 0, 6000);
        gPad->SetLogy();
        h4->Draw("maximum[VFE4_2]>>E3");

	c1->cd(16);
	TH1F*A4 = new TH1F("A4", "A4", 100, 0, 6000);
        gPad->SetLogy();
        h4->Draw("maximum[VFE8_3] >> A4");

        c1->cd(17);
        TH1F*B4 = new TH1F("B4","B4", 100, 0, 6000);
        gPad->SetLogy();
        h4->Draw("maximum[VFE7_1] >> B4");

	c1->cd(18);
        TH1F*C4 = new TH1F("C4","C4", 100, 0, 6000);
        gPad->SetLogy();
        h4->Draw("maximum[VFE3_3] >> C4");

	c1->cd(19);
	TH1F*D4 = new TH1F("D4","D4", 100, 0, 6000);
	gPad->SetLogy();
	h4->Draw("maximum[VFE5_1]>>D4");

	c1->cd(20);
	TH1F*E4 = new TH1F("E4","E4", 100, 0, 6000);
	gPad->SetLogy();
	h4->Draw("maximum[VFE4_3]>>E4");

	c1->cd(21);
	TH1F*A5 = new TH1F("A5", "A5", 100, 0, 6000);
        gPad->SetLogy();
        h4->Draw("maximum[VFE8_4] >> A5");

        c1->cd(22);
        TH1F*B5 = new TH1F("B5","B5", 100, 0, 6000);
        gPad->SetLogy();
        h4->Draw("maximum[VFE7_0] >> B5");

	c1->cd(23);
        TH1F*C5 = new TH1F("C5","C5", 100, 0, 6000);
        gPad->SetLogy();
        h4->Draw("maximum[VFE3_4] >> C5");

	c1->cd(24);
	TH1F*D5 = new TH1F("D5","D5", 100, 0, 6000);
	gPad->SetLogy();
	h4->Draw("maximum[VFE5_0]>>D5");

	c1->cd(25);
	TH1F*E5 = new TH1F("E5","E5", 100, 0, 6000);
	gPad->SetLogy();
	h4->Draw("maximum[VFE4_4]>>E5");

	c1->SaveAs("namemeplease.png");

}
