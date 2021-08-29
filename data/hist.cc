void hist(){
    ifstream file("data");

    TH1F *hist = new TH1F("hist","Histogram",1000,-180,180);

    int N = 1;
    while(N <= 10000){
        double arrive_phi, arrive_theta, relative_path, variation;
        file >> arrive_phi >> arrive_theta >> relative_path >> variation;

        hist->Fill(arrive_phi);
        //hist->Fill(arrive_theta);

        N++;
        std::cout << N << std::endl;
    }

    file.close();
    
    TCanvas *c1 = new TCanvas();
    hist->GetYaxis()->SetRangeUser(0,200);
    hist->Draw();
}
