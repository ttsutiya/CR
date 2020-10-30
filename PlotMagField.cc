void PlotMagField(){

    ifstream in("magfield.dat");

    TCanvas *c2 = new TCanvas("c2", "MagField");

    //c1 -> SetFillColor();
    c2 -> SetGrid();

    Int_t nlines = 0;
    Int_t N;

    in >> N;

    Double_t mag[N], time[N];

    while(nlines < N){
        in >>time[nlines] >>mag[nlines];
        nlines++;
    }
    
    TGraph *gr = new TGraph(N,time,mag);
    gr->Draw("APL");

    gr->SetTitle("Magnetic Field");
    gr->GetXaxis()->SetTitle("time (s)");
    gr->GetYaxis()->SetTitle("B (tesla)");
}
