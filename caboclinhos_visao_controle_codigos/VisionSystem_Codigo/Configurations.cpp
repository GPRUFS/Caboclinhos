#include "Configurations.h"
#include "constantes_robot.h"

Configurations::Configurations(VideoCapture cap, String filename)
{
	fs.open(filename, FileStorage::READ);
	GetAndSetConfigurationsCamera(cap);
    GetVariaveisCampo();

}

void Configurations::GetAndSetConfigurationsCamera(VideoCapture cap)
{
    FileNode data2 = fs["Resolution"];
    Sleep(30);
    cap.set(CV_CAP_PROP_FRAME_WIDTH ,(int)(data2["Width"]));
    Sleep(30);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT , (int)(data2["Height"]));
    Sleep(30);
	FileNode data = fs["Camera_Settings"];
    Sleep(30);
    cap.set(CV_CAP_PROP_EXPOSURE, (int)(data["Exposure"]));
    Sleep(30);
	cap.set(CV_CAP_PROP_CONTRAST, (int)(data["Contrast"]));
	Sleep(30);
	cap.set(CV_CAP_PROP_SATURATION, (int)(data["Saturation"]));
	Sleep(30);
	cap.set(CV_CAP_PROP_EXPOSURE, (int)(data["Exposure"]));
	Sleep(30);
	cap.set(CV_CAP_PROP_BRIGHTNESS, (int)(data["Brightness"]) + 1);
	Sleep(30);
	cap.set(CV_CAP_PROP_BRIGHTNESS, (int)(data["Brightness"]));
	Sleep(30);
}

vector<int> Configurations::GetSettingsAnyData(String dataName)
{
	FileNode data = fs[dataName];
	vector <int> l;
	int i = 0;
	FileNodeIterator it = data.begin(), it_end = data.end();
	for (; it != it_end; ++it)
	{
		l[i] = (int)*it;
		i++;
	}
	return l;
}

Rect Configurations::GetCutFramePoints()
{
	FileNode data = fs["Cut_Frame_Points"];
	Rect cut((int)(data["X"]), (int)(data["Y"]), (int)(data["Width"]), (int)(data["Height"]));
	return cut;
}

void Configurations::GetThresholdColor(Scalar* Threshold, String ColorName)
{
	FileNode data = fs[ColorName];
	Scalar aux1((int)(data["Blue_Min"]), (int)(data["Green_Min"]), (int)(data["Red_Min"]));
	Scalar aux2((int)(data["Blue_Max"]), (int)(data["Green_Max"]), (int)(data["Red_Max"]));
	Threshold[0] = aux1;
	Threshold[1] = aux2;
}

void Configurations::GetConfigurationsElement(Mat *Mascaras)
{
	FileNode data = fs["Mascara"];
	Mat elementOpening = getStructuringElement((int)(data["Format"]), Size((int)(data["Size"]), (int)(data["Size"])), Point(-1, -1));
	Mat elementClosing = getStructuringElement((int)(data["Format"]), Size((int)(data["Size_close"]), (int)(data["Size_close"])), Point(-1, -1));
	Mascaras[0] = elementOpening;
	Mascaras[1] = elementClosing;
}

void Configurations::GetVariaveisCampo()
{
    FileNode data = fs["Variaveis"];
    ftop = (int)(data["ftop"]);
    fbot = (int)(data["fbot"]);
    gtopy = (int)(data["gtopy"]);
    gboty = (int)(data["gboty"]);
    fleftx = (int)(data["fleftx"]);
    frightx = (int)(data["frightx"]);
    gleft = (int)(data["gleft"]);
    gright = (int)(data["gright"]);
    area_left = (int)(data["area_left"]);
    area_right = (int)(data["area_right"]);
    lgoleiro = (int)(data["lgoleiro"]);
    lzagueiro = (int)(data["lzagueiro"]);
    area_topy = (int)(data["area_topy"]);
    area_boty = (int)(data["area_boty"]);
    p_area_b = (int)(data["p_area_b"]);
    p_area_t = (int)(data["p_area_t"]);
    tam_robo = (area_topy - gtopy) / 2;
    diametro_robo = fleftx - gleft;
    meio_campo_x = (frightx - fleftx) / 2 + fleftx;
    meio_campo_y = (ftop - fbot) / 2 + fbot;
}

void Configurations::ReadConfigurationsRobots(String filename)
{
    double k_lin;
    double k_ang;
    double v_max;
    double w_max;

    int zonamorta_d;
    int zonamorta_e;

    double k_lin2;
    double k_ang2;
    double v_max2;
    double w_max2;

    int zonamorta_d2;
    int zonamorta_e2;

    double k_lin3;
    double k_ang3;
    double v_max3;
    double w_max3;

    int zonamorta_d3;
    int zonamorta_e3;

    fs2.open(filename, FileStorage::READ);
    FileNode data = fs2["Variaveis_RB1"];
    if (!data.empty())
    {
        cout << "Leu constantes RB1" << endl;
        k_lin = (double)(data["K_LIN"]);
        k_ang = (double)(data["K_ANG"]);
        v_max = (double)(data["V_MAX"]);
        w_max = (double)(data["W_MAX"]);

        zonamorta_d = (double)(data["ZONA_MORTA_D"]);
        zonamorta_e = (double)(data["ZONA_MORTA_E"]);
    }
    else
    {
        cout << "erro" << endl;
        k_lin = 0.008;
        k_ang = 0.288;
        v_max = 0.440;
        w_max = -0.850;

        zonamorta_d = 35;
        zonamorta_e = 35;
    }

    FileNode data2 = fs2["Variaveis_RB2"];
    if (!data2.empty())
    {
        cout << "Leu constantes RB2" << endl;
        k_lin2 = (double)(data2["K_LIN"]);
        k_ang2 = (double)(data2["K_ANG"]);
        v_max2 = (double)(data2["V_MAX"]);
        w_max2 = (double)(data2["W_MAX"]);

        zonamorta_d2 = (double)(data2["ZONA_MORTA_D"]);
        zonamorta_e2 = (double)(data2["ZONA_MORTA_E"]);
    }
    else
    {
        cout << "erro" << endl;
        k_lin2 = 0.002;
        k_ang2 = 0.1;
        v_max2 = 1;
        w_max2 = -1;

        zonamorta_d2 = 35;
        zonamorta_e2 = 35;
    }


    FileNode data3 = fs2["Variaveis_RB3"];
    if (!data3.empty())
    {
        cout << "Leu constantes RB3" << endl;
        k_lin3 = (double)(data2["K_LIN"]);
        k_ang3 = (double)(data2["K_ANG"]);
        v_max3 = (double)(data2["V_MAX"]);
        w_max3 = (double)(data2["W_MAX"]);

        zonamorta_d3 = (double)(data2["ZONA_MORTA_D"]);
        zonamorta_e3 = (double)(data2["ZONA_MORTA_E"]);
    }
    else
    {
        cout << "erro" << endl;
        k_lin3 = 0.002;
        k_ang3 = 0.1;
        v_max3 = 1;
        w_max3 = -1;

        zonamorta_d3 = 35;
        zonamorta_e3 = 35;
    }

    rb1[0] = v_max;
    rb1[1] = k_lin;
    rb1[2] = w_max;
    rb1[3] = k_ang;

    rb2[0] = v_max2;
    rb2[1] = k_lin2;
    rb2[2] = w_max2;
    rb2[3] = k_ang2;

    rb3[0] = v_max3;
    rb3[1] = k_lin3;
    rb3[2] = w_max3;
    rb3[3] = k_ang3;

    zonamorta_rb1[0] = zonamorta_d;
    zonamorta_rb1[1] = zonamorta_e;

    zonamorta_rb2[0] = zonamorta_d2;
    zonamorta_rb2[1] = zonamorta_e2;

    zonamorta_rb3[0] = zonamorta_d3;
    zonamorta_rb3[1] = zonamorta_e3;
}

void Configurations::WriteConfigurationsRobots(double *rb1, double *rb2, double *rb3, int *zona1, int *zona2, int *zona3, String filename)
{
    fs2.open(filename, FileStorage::WRITE);
    fs2 << "Variaveis_RB1";
    fs2 << "{" << "V_MAX" << rb1[0];
    fs2 <<        "K_LIN" << rb1[1];
    fs2 <<        "W_MAX" << rb1[2];
    fs2 <<        "K_ANG" << rb1[3];
    fs2 <<        "ZONA_MORTA_D" << zona1[0];
    fs2 <<        "ZONA_MORTA_E" << zona1[1] << "}";
    fs2 << "Variaveis_RB2";
    fs2 << "{" << "V_MAX" << rb2[0];
    fs2 <<        "K_LIN" << rb2[1];
    fs2 <<        "W_MAX" << rb2[2];
    fs2 <<        "K_ANG" << rb2[3];
    fs2 <<        "ZONA_MORTA_D" << zona2[0];
    fs2 <<        "ZONA_MORTA_E" << zona2[1] << "}";
    fs2 << "Variaveis_RB3";
    fs2 << "{" << "V_MAX" << rb3[0];
    fs2 <<        "K_LIN" << rb3[1];
    fs2 <<        "W_MAX" << rb3[2];
    fs2 <<        "K_ANG" << rb3[3];
    fs2 <<        "ZONA_MORTA_D" << zona3[0];
    fs2 <<        "ZONA_MORTA_E" << zona3[1] << "}";
}


Configurations::~Configurations()
{
	fs.release();
    fs2.release();
}
