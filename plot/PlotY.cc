void PlotY(){

    ifstream in("data/pos.dat");

    TCanvas *c6 = new TCanvas("c6", "y");

    //c1 -> SetFillColor();
    c6 -> SetGrid();

    Int_t nlines = 0;
    Int_t N;
    Double_t temp;

    in >> N;
    in >> temp >> temp >> temp >> temp >> temp >> temp;

    Double_t y[N], t[N];

    while(nlines < N){
        in >> t[nlines] >> temp >> y[nlines] >> temp;
        nlines++;
    }
    
    TGraph *gr = new TGraph(N,t,y);
    gr->Draw("APL");

    gr->SetTitle("y");
    gr->GetXaxis()->SetTitle("time (s)");
    gr->GetYaxis()->SetTitle("y (m)");
}
