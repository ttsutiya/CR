void PlotX(){

    ifstream in("pos.dat");
    //ifstream in("../data/pos/pos_1.dat");
    
    TCanvas *c5 = new TCanvas("c5", "x");

    //c1 -> SetFillColor();
    c5 -> SetGrid();

    Int_t nlines = 0;
    Int_t N;
    Double_t temp;

    in >> N;
    in >> temp >> temp >> temp >> temp >> temp >> temp;

    Double_t x[N], t[N];

    while(nlines < N){
        in >> t[nlines] >> x[nlines] >> temp >> temp;
        nlines++;
    }
    
    TGraph *gr = new TGraph(N,t,x);
    gr->Draw("APL");

    gr->SetTitle("x");
    gr->GetXaxis()->SetTitle("time (s)");
    gr->GetYaxis()->SetTitle("x (m)");
}
