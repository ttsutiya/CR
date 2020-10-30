void PlotFrequency(){

    ifstream in("frequency.dat");

    TCanvas *c3 = new TCanvas("c3", "Frequency");

    //c1 -> SetFillColor();
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
    gr->Draw("AP");

    gr->SetTitle("Frequency");
    gr->GetXaxis()->SetTitle("time (s)");
    gr->GetYaxis()->SetTitle("frequency (Hz)");

    TPaveText *title = new TPaveText(50,80,80,100);
       title->SetFillColor(24);
       title->AddText("Frequency");
       TText *click=title->AddText("q = 1 [C], m = 2 [kg], B(r) = 1E3 [T], B = 1 [T]");
       click->SetTextColor(9);
       title->Draw();
}
