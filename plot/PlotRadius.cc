void PlotRadius(){

    ifstream in("data/rad.dat");

    TCanvas *c4 = new TCanvas("c4", "Gyroradius");

    //c1 -> SetFillColor();
    c4 -> SetGrid();

    Int_t N;
    in >> N;

    std::vector<Double_t> time(N);
    std::vector<Double_t> rad(N);

    for(int i = 0; i < N; i++){
        in >> time[i];
        in >> rad[i];
    }

    TGraph *gr = new TGraph(N,&time[0],&rad[0]);
    gr->Draw("APL");

    gr->SetTitle("Gyroradius");
    gr->GetXaxis()->SetTitle("time (s)");
    gr->GetYaxis()->SetTitle("radius (m)");
}
