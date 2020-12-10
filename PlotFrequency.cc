void PlotFrequency(){

    ifstream in("frequency.dat");

    TCanvas *c3 = new TCanvas("c3", "Frequency");

    c3 -> SetGrid();

    Int_t nlines = 0;
    Int_t N;

    in >> N;

    Double_t freq[N], time[N];

    while(nlines < N){
        in >>time[nlines] >>freq[nlines];
        nlines++;
    }
    
    TGraph *gr = new TGraph(N,time,freq);
    gr->Draw("APL");

    gr->SetTitle("Frequency");
    gr->GetXaxis()->SetTitle("time (s)");
    gr->GetYaxis()->SetTitle("frequency (Hz)");

}
