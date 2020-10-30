void PlotZ(){

    ifstream in("pos.dat");

    TCanvas *c7 = new TCanvas("c7", "x");

    //c1 -> SetFillColor();
    c7 -> SetGrid();

    Int_t nlines = 0;
    Int_t N;
    Double_t temp;

    in >> N;
    in >> temp >> temp >> temp >> temp >> temp >> temp;

    Double_t z[N], t[N];

    while(nlines < N){
        in >> t[nlines] >> temp >> temp >> z[nlines] ;
        nlines++;
    }
    
    TGraph *gr = new TGraph(N,t,z);
    gr->Draw("APL");

    gr->SetTitle("z");
    gr->GetXaxis()->SetTitle("time (s)");
    gr->GetYaxis()->SetTitle("z (m)");
}
