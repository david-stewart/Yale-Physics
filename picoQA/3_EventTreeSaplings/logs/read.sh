root -l 16.root<<EOF
    TCanvas *c1 = new TCanvas("c1");
    c1->SetLogz();

    TH2D* h = h_jet_pt_dphi_500206;
    h->GetXaxis()->SetTitle("#pi #Delta #phi");
    // h->Draw("colz");

    int i1 = h->GetYaxis()->FindBin(4.1);
    int i2 = h->GetYaxis()->FindBin(9.95);
    TH1D* four_ten = h->ProjectionX("four_ten",i1,i2)
    four_ten->GetYaxis()->SetTitle("Number of jets, p_{T} 4-10 [GeV/c]")
    four_ten->SetMarkerStyle(kFullCircle)
    four_ten->SetMarkerColor(kBlack)
    //four_ten->Draw("PE")
    
    i1 = h->GetYaxis()->FindBin(10.1);
    i2 = h->GetYaxis()->FindBin(14.95);
    TH1D* ten_15 = h->ProjectionX("ten_15",i1,i2)
    ten_15->GetYaxis()->SetTitle("Number of jets, p_{T} 10-15 [GeV/c]")
    ten_15->SetMarkerStyle(kFullCircle)
    ten_15->SetMarkerColor(kBlue)
    ten_15->Draw("PE")

    i1 = h->GetYaxis()->FindBin(15.1);
    i2 = h->GetYaxis()->FindBin(19.95);
    TH1D* fifteen_20 = h->ProjectionX( "fifteen_20",i1,i2);
    fifteen_20->GetYaxis()->SetTitle("Number of jets, p_{T} 15-20 [GeV/c]");
    fifteen_20->SetMarkerStyle(kFullCircle);
    fifteen_20->SetMarkerColor(kGreen+2);
    //fifteen_20->Draw("PE");
    
    TCanvas *c2 = new TCanvas("c2");
    c2->WaitPrimitive();
EOF
