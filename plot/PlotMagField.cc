void PlotMagField(){

    ifstream in("data/magfield.dat");
    //ifstream in("data//mag/magfield_1.dat");

    TCanvas *c2 = new TCanvas("c2", "MagField");

    c2 -> SetGrid();

    Int_t N;
    in >> N;

    std::vector<Double_t> time(N);
    std::vector<Double_t> mag(N);

    for(int i = 0; i < N; i++){
        in >> time[i];
        in >> mag[i];
    }
    
    TGraph *gr = new TGraph(N,&time[0],&mag[0]);
    gr->Draw("APL");

    gr->SetTitle("Magnetic field");
    gr->GetXaxis()->SetTitle("time (s)");
    gr->GetYaxis()->SetTitle("B (tesla)");
}
