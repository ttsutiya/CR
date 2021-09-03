void hist(){
    TH1F *hist1 = new TH1F("hist","Arrive Phi",500,-180,180);
    TH1F *hist2 = new TH1F("hist","Arrive Theta",500,0,90);
    TH1F *hist3 = new TH1F("hist","Relative Path",1000,0,30);
    TH1F *hist4 = new TH1F("hist","Deviation",1000,0,130);
    
    int N = 1;
    double max_path = 0;
    double max_var = 0;

    ifstream file("data");

    while(N <= 1000){
        double arrive_phi, arrive_theta, relative_path, deviation;
        file >> arrive_phi >> arrive_theta >> relative_path >> deviation;

        if(relative_path > max_path) max_path = relative_path;
        if(deviation > max_var) max_var = deviation;

        hist1->Fill(arrive_phi);
        hist2->Fill(arrive_theta);
        hist3->Fill(relative_path);
        hist4->Fill(deviation);

        N++;
    }

    file.close();

    cout << "max_path = " << max_path << endl;
    cout << "max_var = " << max_var << endl;

//##################################################
    TCanvas *c1 = new TCanvas();

    c1->SetTickx();
    c1->SetTicky();
    c1->SetGridx();
    c1->SetGridy();

    hist1->GetXaxis()->SetTitle("Distribuition");
    hist1->GetYaxis()->SetTitle("Entries");
    hist1->GetYaxis()->SetRangeUser(0,100);
    hist1->Draw();
    hist1->Fit("pol0");
  
//##################################################
    TCanvas *c2 = new TCanvas();
//    TF1 *f = new TF1("fit","[0]*TMath::Power(TMath::Cos([1]*x-[2]),[3])+[4]",0,90);
//    f->SetParameters(0,40);
//    f->SetParameters(1,0);
//    f->SetParameters(2,55);
//    f->SetParameters(3,1);
//    f->SetParameters(4,0);

    c2->SetTickx();
    c2->SetTicky();
    c2->SetGridx();
    c2->SetGridy();

    hist2->GetXaxis()->SetTitle("Distribuition");
    hist2->GetYaxis()->SetTitle("Entries");
    hist2->GetYaxis()->SetRangeUser(0,100);
    hist2->Draw();
    hist2->Fit("fit");

//##################################################
    gStyle->SetOptLogx();
    gStyle->SetOptLogy();

    TCanvas *c3 = new TCanvas();

    c3->SetTickx();
    c3->SetTicky();
    c3->SetGridx();
    c3->SetGridy();

    hist3->GetXaxis()->SetTitle("Distribuition");
    hist3->GetYaxis()->SetTitle("Entries");
    hist3->Draw();
//##################################################

    gStyle->SetOptLogx(0);
    gStyle->SetOptLogy(0);

    TCanvas *c4 = new TCanvas();

    c4->SetTickx();
    c4->SetTicky();
    c4->SetGridx();
    c4->SetGridy();

    hist4->GetXaxis()->SetTitle("Distribuition");
    hist4->GetYaxis()->SetTitle("Entries");
    hist4->Draw();
}
