void PlotRadius(){

    ifstream in("rad.dat");

    TCanvas *c4 = new TCanvas("c4", "Gyroradius");

    //c1 -> SetFillColor();
    c4 -> SetGrid();

    Int_t nlines = 0;
    Int_t N;

    in >> N;

    Double_t rad[N], time[N];

    while(nlines < N){
        in >>time[nlines] >>rad[nlines];
        nlines++;
    }
    
    TGraph *gr = new TGraph(N,time,rad);
    gr->Draw("APL");

    gr->SetTitle("Gyro Radius");
    gr->GetXaxis()->SetTitle("time (s)");
    gr->GetYaxis()->SetTitle("radius (m)");
}
