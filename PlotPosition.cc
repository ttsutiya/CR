void PlotPosition(){

ifstream in("pos.dat");

const Double_t au = 149597870700;

Int_t N;
Double_t x,y,z,t;
Double_t x_max, y_max, z_max, x_min, y_min, z_min;

TCanvas *c1 = new TCanvas("c1", "Position");

TView *view = TView::CreateView(1);

in >> N;
in >> x_max >> y_max >> z_max >> x_min >> y_min >> z_min; 

view->SetRange(x_min/au, y_min/au, z_min/au, x_max/au, y_max/au, z_max/au);

TPolyLine3D *h123 = new TPolyLine3D(N); 
     
    for (Int_t i=0;i<N;i++){
        in >> t >> x >> y >> z;
        h123->SetPoint(i,x/au,y/au,z/au);
    }

h123->Draw();


//TPaveText *title = new TPaveText(0.1,0.75,0.8,0.97);
//   title->SetFillColor(24);
//   title->AddText("Trajectory of a particle in a magnetic field");
//   TText *click=title->AddText("q = 1 [C], m = 2 [kg], B0 = 1E4 [T]");
//   click->SetTextColor(9);
//   title->Draw();
   
   TAxis3D *rulers = new TAxis3D();
    rulers->SetXTitle("x [AU]");
    rulers->SetYTitle("y [AU]");
    rulers->SetZTitle("z [AU]"); 
    rulers->Draw();  
    
in.close();
}