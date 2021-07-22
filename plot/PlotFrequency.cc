void PlotFrequency(){

    ifstream in("data/frequency.dat");

    TCanvas *c3 = new TCanvas("c3", "Frequency");

    c3 -> SetGrid();

    Int_t N;
    in >> N;

    std::vector<Double_t> time(N);
    std::vector<Double_t> freq(N);

    for(int i = 0; i < N; i++){
        in >> time[i];
        in >> freq[i];
    }

    TGraph *gr = new TGraph(N,&time[0],&freq[0]);
    gr->Draw("APL");

    gr->SetTitle("Frequency");
    gr->GetXaxis()->SetTitle("time (s)");
    gr->GetYaxis()->SetTitle("frequency (Hz)");

}
