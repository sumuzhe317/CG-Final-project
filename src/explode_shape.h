// 本头文件用于存储各种烟花爆炸模型的顶点
// float* vertices_arr[] 存储各个模型顶点数组的首地址
// int vertices_num[]  存储各个模型顶点数组的顶点数量
// 下标需要与 particle.h 中的 enum fireworktype { } 对应

#ifndef __EXPLODE_SHAPE_H__
#define __EXPLODE_SHAPE_H__

float diamond_vertices[] = {
-0.452410,0.392288,0.190160,
-0.184187,0.392288,0.451414,
0.000000,0.508361,0.000000,
-0.706109,-0.035972,0.711629,
-0.199103,-0.738043,0.487970,
-0.398206,-0.048788,0.975941,
-0.455617,0.392288,-0.182488,
-1.007178,-0.035972,0.008509,
-0.489047,-0.738043,0.205559,
-0.978095,-0.048788,0.411118,
-0.191930,0.392288,-0.448236,
-0.718256,-0.035972,-0.699595,
-0.492514,-0.738043,-0.197266,
-0.985029,-0.048788,-0.394532,
0.184187,0.392288,-0.451414,
-0.008589,-0.035972,-0.997886,
-0.207473,-0.738043,-0.484536,
-0.414946,-0.048788,-0.969071,
0.452410,0.392288,-0.190159,
0.706109,-0.035972,-0.711629,
0.199103,-0.738043,-0.487971,
0.398206,-0.048788,-0.975941,
0.455617,0.392288,0.182488,
1.007178,-0.035972,-0.008509,
0.489047,-0.738043,-0.205559,
0.978095,-0.048788,-0.411118,
0.191930,0.392288,0.448236,
0.718256,-0.035972,0.699595,
0.492514,-0.738043,0.197266,
0.985029,-0.048788,0.394532,
0.008589,-0.035972,0.997886,
0.207473,-0.738043,0.484535,
0.414946,-0.048788,0.969071,
-0.398206,0.034935,0.975941,
-0.706109,0.022119,0.711629,
-0.978095,0.034936,0.411118,
-1.007178,0.022120,0.008509,
-0.985029,0.034936,-0.394532,
-0.718256,0.022120,-0.699595,
-0.414946,0.034936,-0.969071,
-0.008589,0.022120,-0.997886,
0.398206,0.034936,-0.975941,
0.706109,0.022120,-0.711629,
0.978095,0.034936,-0.411118,
1.007178,0.022120,-0.008509,
0.985029,0.034936,0.394532,
0.718256,0.022119,0.699595,
0.414946,0.034935,0.969071,
0.008589,0.022119,0.997886,
-0.359222,0.239081,0.880398,
-0.620781,0.239082,0.625635,
-0.882341,0.239082,0.370871,
-0.885468,0.239082,0.007481,
-0.888596,0.239082,-0.355908,
-0.631460,0.239082,-0.615054,
-0.374324,0.239082,-0.874201,
-0.007551,0.239082,-0.877299,
0.359222,0.239082,-0.880398,
0.888596,0.239082,0.355908,
0.631460,0.239082,0.615054,
0.374324,0.239081,0.874201,
0.007551,0.239081,0.877299,
0.000000,-1.346046,-0.000000,
0.620781,0.239082,-0.625634,
0.882341,0.239082,-0.370870,
0.885468,0.239082,-0.007481
};


float heart_vertices[] = {
0.247023,0.497924,0.252634,
-0.049764,0.302951,0.273731,
-0.042510,0.078193,0.396048,
0.482619,-0.283723,-0.225702,
0.289784,-0.549308,-0.150439,
0.223271,-0.429739,-0.285400,
-0.336052,-0.375220,0.336869,
-0.074706,-0.586452,0.283292,
-0.029227,-0.362640,0.389120,
0.503171,-0.383580,0.145697,
0.300498,-0.606506,-0.013812,
0.602161,-0.291189,-0.007493,
-0.067109,-0.763755,-0.063562,
-0.377888,-0.486640,-0.205432,
-0.055083,-0.721256,-0.145597,
0.353915,0.185007,-0.351716,
-0.040746,0.094309,-0.352339,
0.276612,0.403199,-0.290467,
0.471040,0.286684,-0.311022,
0.468053,0.058279,-0.334154,
0.634358,0.269121,0.273479,
0.661892,-0.004917,0.254169,
0.754244,0.200235,0.141549,
-0.599714,0.526096,0.051253,
-0.778652,0.340404,0.115145,
-0.533928,0.481910,0.231780,
-0.543595,-0.007387,0.365439,
-0.225555,-0.171294,0.412496,
-0.467089,0.250634,0.374030,
-0.156852,-0.482625,-0.291554,
-0.351018,-0.253004,-0.334636,
-0.143353,-0.054064,-0.379188,
-0.457160,0.222723,-0.349839,
0.272469,-0.155481,-0.360276,
-0.025618,-0.311703,-0.364930,
-0.281991,-0.151716,-0.368243,
-0.710383,0.434281,-0.062543,
-0.837054,0.223885,-0.055043,
0.621315,0.105681,-0.264388,
0.720615,0.247441,-0.174067,
0.215824,0.554112,0.154315,
0.240588,0.583539,-0.013712,
-0.038960,0.405177,0.142998,
0.136905,-0.058394,-0.376635,
0.111149,-0.727133,-0.052016,
0.057669,-0.725310,0.170534,
0.284071,-0.567568,0.178278,
0.521200,-0.355818,-0.104709,
0.703222,-0.027588,-0.151185,
0.773229,0.069009,0.017724,
-0.397366,-0.490169,0.213149,
-0.368719,-0.599877,0.024091,
-0.104237,-0.726290,0.158969,
0.091233,-0.673614,-0.160290,
0.059500,-0.546134,-0.262961,
0.357630,-0.234016,-0.314539,
0.540315,-0.073003,-0.287730,
-0.591056,-0.061205,-0.315111,
-0.038244,0.406656,-0.112324,
-0.284240,0.554307,-0.051119,
-0.593079,-0.370788,0.095353,
-0.583224,-0.379958,-0.070881,
-0.819553,-0.004968,-0.064501,
-0.765347,-0.122696,0.094892,
0.511297,0.564434,-0.026476,
0.650171,0.418995,0.159522,
0.731754,0.348890,-0.061422,
0.144540,-0.506344,0.310133,
0.316806,-0.257108,0.366583,
0.192953,-0.111212,0.414767,
0.522232,0.020135,0.357166,
0.430052,0.239605,0.373493,
-0.313797,0.395313,0.308611,
-0.291010,0.517355,0.194925,
-0.811328,0.095288,0.163886,
-0.704071,0.220663,0.277910,
-0.328827,0.464316,-0.251470,
-0.686401,0.290688,-0.240138,
0.431731,0.560958,0.141246,
0.236266,0.538745,-0.166623,
-0.027141,0.291194,-0.251696,
0.471994,0.490602,-0.200169,
-0.673591,-0.103124,0.267523,
-0.496582,0.547306,-0.112274,
-0.586793,0.431499,-0.213304,
-0.418533,0.572774,0.075196,
0.464502,-0.273277,0.281883,
0.723382,-0.038342,0.124001,
-0.681783,-0.177715,-0.167113,
-0.749893,0.068050,-0.223475,
0.441549,0.446591,0.273821,
0.294020,0.338691,0.356012
};


float bird_vertices[] = {
0.754686,0.676922,0.443937,
1.045030,0.766134,0.490552,
1.044765,0.766682,0.490055,
0.439880,0.605401,0.405182,
0.156171,0.516414,0.348220,
-0.030705,0.365610,0.246714,
-0.175133,0.186980,0.126869,
-0.169794,0.175937,0.136895,
1.045294,0.765587,0.491050,
-0.164454,0.164893,0.146920,
1.045558,0.765039,0.491547,
-0.159115,0.153850,0.156946,
1.045823,0.764492,0.492043,
0.156171,0.516414,0.348220,
-0.153776,0.142807,0.166972,
0.762905,0.659921,0.459371,
1.046088,0.763945,0.492541,
0.456750,0.570507,0.436861,
0.180501,0.466093,0.393904,
-0.004009,0.310393,0.296843,
-0.148436,0.131763,0.176997,
-0.066188,0.158712,0.037711,
-0.060848,0.147669,0.047736,
0.042758,0.130444,-0.051448,
0.048097,0.119401,-0.041422,
0.151702,0.102177,-0.140606,
0.157042,0.091133,-0.130581,
0.260648,0.073909,-0.229765,
0.265988,0.062865,-0.219738,
0.369593,0.045641,-0.318922,
0.374933,0.034598,-0.308897,
-0.055509,0.136625,0.057762,
0.053436,0.108358,-0.031396,
0.162382,0.080090,-0.120554,
0.271327,0.051822,-0.209713,
0.380272,0.023554,-0.298872,
-0.050170,0.125582,0.067788,
0.058776,0.097314,-0.021371,
0.167721,0.069046,-0.110529,
0.276667,0.040779,-0.199688,
0.385611,0.012511,-0.288845,
-0.044830,0.114539,0.077813,
0.064115,0.086271,-0.011345,
0.173061,0.058003,-0.100504,
0.282006,0.029735,-0.189661,
0.390951,0.001468,-0.278820,
-0.039491,0.103495,0.087839,
0.069455,0.075228,-0.001320,
0.178399,0.046960,-0.090478,
0.287345,0.018692,-0.179636,
0.396290,-0.009576,-0.268795,
0.514020,0.224271,-0.199078,
0.654196,0.383941,-0.041840,
0.796290,0.520342,0.150552,
0.947350,0.650726,0.339302,
1.106598,0.791262,0.499141,
1.106660,0.791133,0.499258,
1.106723,0.791005,0.499374,
1.106785,0.790876,0.499491,
1.106846,0.790748,0.499608,
0.540717,0.169054,-0.148949,
0.677096,0.336577,0.001159,
0.811204,0.489497,0.178555,
0.953751,0.637487,0.351321,
1.106909,0.790619,0.499724,
1.097410,0.785105,0.494572,
1.097509,0.784901,0.494757,
1.086750,0.779528,0.491268,
1.086887,0.779245,0.491525,
1.074499,0.774573,0.489343,
1.074677,0.774206,0.489676,
1.060541,0.770278,0.488903,
1.060760,0.769823,0.489316,
1.097607,0.784698,0.494942,
1.087024,0.778962,0.491782,
1.074854,0.773839,0.490009,
1.060980,0.769368,0.489730,
1.097706,0.784494,0.495126,
1.087161,0.778679,0.492039,
1.075031,0.773472,0.490343,
1.061200,0.768913,0.490144,
1.097805,0.784290,0.495312,
1.087298,0.778396,0.492296,
1.075208,0.773105,0.490676,
1.061421,0.768457,0.490557,
1.097902,0.784087,0.495496,
1.087435,0.778112,0.492554,
1.075386,0.772738,0.491009,
1.061641,0.768002,0.490970,
0.806735,0.653395,0.432582,
0.533556,0.552219,0.379714,
0.283971,0.438775,0.311426,
0.104936,0.282126,0.207684,
0.847691,0.647903,0.408426,
0.607429,0.534965,0.325289,
0.385459,0.412130,0.230829,
0.213882,0.253858,0.118526,
0.885814,0.643431,0.386861,
0.678342,0.518754,0.273609,
0.484868,0.386194,0.152197,
0.322827,0.225590,0.029367,
0.921150,0.639965,0.367842,
0.746273,0.503596,0.224693,
0.582110,0.360999,0.075615,
0.431773,0.197322,-0.059791,
0.914394,0.653938,0.355157,
0.730965,0.535257,0.195948,
0.558909,0.408986,0.032050,
0.405076,0.252539,-0.109919,
0.878698,0.658148,0.373500,
0.662641,0.551230,0.244126,
0.461373,0.434789,0.108081,
0.296130,0.280807,-0.020761,
0.840212,0.663372,0.394382,
0.591336,0.568251,0.295071,
0.361678,0.461317,0.186174,
0.187185,0.309075,0.068397,
0.798888,0.669626,0.417847,
0.517073,0.586312,0.348764,
0.259912,0.488537,0.266250,
0.078240,0.337342,0.157556,
-0.117268,0.801630,-0.875410,
-0.015640,0.945544,-1.119515,
-0.240129,0.667658,-0.616859,
-0.330887,0.521954,-0.376330,
-0.329019,0.338671,-0.192113,
-0.287263,0.138812,-0.032602,
-0.279839,0.148457,-0.022460,
-0.272416,0.158102,-0.012319,
-0.264992,0.167747,-0.002178,
-0.257568,0.177391,0.007963,
-0.105840,0.816477,-0.859799,
-0.013800,0.947935,-1.117001,
-0.216671,0.698133,-0.584816,
-0.297059,0.565902,-0.330119,
-0.291901,0.386895,-0.141407,
-0.250144,0.187036,0.018104,
-0.162546,0.112201,-0.098591,
-0.155122,0.121846,-0.088450,
-0.037828,0.085590,-0.164582,
-0.030404,0.095235,-0.154441,
0.086890,0.058980,-0.230573,
0.094313,0.068624,-0.220431,
0.211608,0.032369,-0.296563,
0.219032,0.042014,-0.286422,
0.336325,0.005758,-0.362553,
0.343749,0.015403,-0.352412,
-0.147698,0.131491,-0.078309,
-0.022980,0.104880,-0.144300,
0.101737,0.078269,-0.210290,
0.226455,0.051659,-0.276280,
0.351173,0.025048,-0.342270,
-0.140275,0.141136,-0.068168,
-0.015556,0.114525,-0.134159,
0.109161,0.087914,-0.200149,
0.233879,0.061303,-0.266139,
0.358596,0.034693,-0.332129,
-0.132851,0.150781,-0.058027,
-0.008133,0.124170,-0.124018,
0.116585,0.097559,-0.190008,
0.241303,0.070948,-0.255998,
0.366020,0.044338,-0.321988,
-0.125427,0.160425,-0.047886,
-0.000709,0.133815,-0.113877,
0.124008,0.107204,-0.179867,
0.248727,0.080593,-0.245857,
0.373444,0.053982,-0.311847,
0.294569,0.205617,-0.522064,
0.227364,0.404069,-0.679685,
0.140250,0.598667,-0.839019,
0.061421,0.789744,-1.003574,
0.005597,0.979813,-1.172476,
0.331688,0.253841,-0.471358,
0.259203,0.445435,-0.636191,
0.160985,0.625606,-0.810694,
0.070321,0.801307,-0.991416,
0.006029,0.980374,-1.171886,
0.005169,0.971837,-1.163711,
0.002976,0.964381,-1.154100,
-0.001127,0.957488,-1.143573,
-0.007286,0.951196,-1.132067,
0.005853,0.972726,-1.162776,
0.003928,0.965618,-1.152799,
0.000107,0.959091,-1.141888,
-0.005756,0.953184,-1.129976,
-0.063654,0.811448,-0.889393,
-0.133806,0.681579,-0.633376,
-0.180588,0.540410,-0.393675,
-0.167183,0.360285,-0.207397,
-0.025001,0.807431,-0.917328,
-0.054580,0.666041,-0.680259,
-0.066613,0.515584,-0.456113,
-0.042465,0.333674,-0.273387,
0.010172,0.804413,-0.943625,
0.020978,0.651527,-0.725448,
0.044750,0.491458,-0.517381,
0.082252,0.307063,-0.339377,
0.041925,0.802377,-0.968312,
0.092840,0.638046,-0.768930,
0.153391,0.468065,-0.577424,
0.206970,0.280452,-0.405367,
0.032532,0.790173,-0.981143,
0.071556,0.610394,-0.798005,
0.121132,0.426155,-0.621490,
0.169852,0.232228,-0.456073,
0.000279,0.791560,-0.957139,
-0.000854,0.623164,-0.755271,
0.012083,0.449017,-0.562005,
0.045133,0.258839,-0.390083,
-0.035400,0.793921,-0.931533,
-0.076955,0.636970,-0.710826,
-0.099678,0.472626,-0.501282,
-0.079584,0.285449,-0.324093,
-0.074565,0.797273,-0.904298,
-0.156724,0.651805,-0.664683,
-0.214040,0.496949,-0.439372,
-0.204302,0.312060,-0.258103,
1.149376,0.535507,-0.850007,
1.141174,0.548370,-0.853732,
1.131896,0.548370,-0.866402,
1.130820,0.535507,-0.875345,
1.139022,0.522644,-0.871620,
1.148299,0.522644,-0.858950,
1.115932,0.434501,-0.763879,
1.081758,0.488096,-0.779404,
1.043099,0.488096,-0.832195,
1.038616,0.434501,-0.869461,
1.072789,0.380906,-0.853936,
1.111448,0.380906,-0.801146,
1.013084,0.361863,-0.685667,
0.977197,0.417181,-0.701451,
0.937220,0.417181,-0.756043,
0.933005,0.361863,-0.795021,
0.968915,0.306436,-0.779372,
1.009005,0.306436,-0.724626,
0.901816,0.295607,-0.612187,
0.869832,0.346237,-0.627027,
0.833857,0.346237,-0.676153,
0.829364,0.295607,-0.711124,
0.861442,0.244501,-0.696840,
0.897882,0.244501,-0.647079,
0.791110,0.231156,-0.536567,
0.761935,0.278582,-0.550804,
0.728621,0.278582,-0.596299,
0.723854,0.231156,-0.628410,
0.753148,0.183127,-0.614872,
0.787046,0.183127,-0.568581,
0.689953,0.163936,-0.451938,
0.655779,0.217532,-0.467462,
0.617121,0.217532,-0.520253,
0.612637,0.163936,-0.557519,
0.646810,0.110341,-0.541995,
0.685469,0.110341,-0.489204,
0.539637,-0.006929,-0.221935,
0.471774,0.132153,-0.272313,
0.375530,0.132153,-0.403741,
0.347987,-0.006929,-0.483646,
0.415753,-0.144985,-0.432428,
0.511265,-0.144985,-0.301999,
0.480610,-0.042585,-0.141907,
0.406494,0.122179,-0.206547,
0.293126,0.122179,-0.361359,
0.253875,-0.042585,-0.451529,
0.327990,-0.207349,-0.386889,
0.441358,-0.207349,-0.232079,
0.379447,-0.066494,-0.030282,
0.298205,0.124964,-0.108229,
0.166706,0.124964,-0.287800,
0.116920,-0.066494,-0.388783,
0.198139,-0.257402,-0.310375,
0.329215,-0.257402,-0.131381,
0.272748,-0.074448,0.079752,
0.188497,0.139823,-0.011969,
0.041819,0.139823,-0.212267,
-0.020190,-0.074448,-0.320277,
0.064059,-0.288227,-0.228160,
0.210361,-0.288227,-0.028374,
0.160390,-0.068319,0.184180,
0.076604,0.161813,0.080908,
-0.080502,0.161813,-0.133631,
-0.153665,-0.068319,-0.244684,
-0.069858,-0.298262,-0.141278,
0.087107,-0.298262,0.073069,
0.042252,-0.049979,0.278987,
-0.038239,0.185988,0.169071,
-0.199220,0.185988,-0.050760,
-0.279710,-0.049979,-0.160676,
-0.199220,-0.285947,-0.050760,
-0.038239,-0.285947,0.169071,
-0.053419,-0.013556,0.343124,
-0.130284,0.217798,0.233337,
-0.288273,0.217798,0.017592,
-0.369736,-0.013556,-0.088828,
-0.292948,-0.245424,0.020678,
-0.134637,-0.245424,0.236862,
-0.150491,0.042680,0.396014,
-0.224527,0.261018,0.292959,
-0.373562,0.261018,0.089442,
-0.449461,0.042680,-0.012251,
-0.375888,-0.176944,0.090246,
-0.225997,-0.176944,0.294933,
-0.252478,0.095927,0.439591,
-0.320961,0.292616,0.347963,
-0.455111,0.292616,0.164773,
-0.521791,0.095927,0.071824,
-0.453926,-0.102176,0.162893,
-0.318813,-0.102176,0.347400,
-0.362895,0.123386,0.475786,
-0.419579,0.289560,0.398381,
-0.532946,0.289560,0.243570,
-0.589629,0.123386,0.166164,
-0.532945,-0.042789,0.243570,
-0.419579,-0.042789,0.398381,
-0.452003,0.112447,0.492455,
-0.504404,0.242621,0.434384,
-0.592876,0.242621,0.313570,
-0.632419,0.112447,0.246083,
-0.581157,-0.023143,0.301149,
-0.489026,-0.023143,0.426960,
-0.539869,0.078152,0.496140,
-0.577002,0.166171,0.457421,
-0.636753,0.166171,0.375827,
-0.662456,0.078152,0.328737,
-0.626335,-0.014681,0.364787,
-0.563332,-0.014681,0.450821,
-0.627238,0.034515,0.494632,
-0.644710,0.077917,0.475269,
-0.674207,0.077917,0.434988,
-0.687392,0.034515,0.412487,
-0.670300,-0.010693,0.430847,
-0.649479,-0.010848,0.458592,
-0.639583,-0.010693,0.472795,
-0.714856,-0.004452,0.495720,
-0.714859,-0.004440,0.495715,
-0.714861,-0.004435,0.495712,
-0.714873,-0.004435,0.495696,
-0.714877,-0.004446,0.495692,
-0.714878,-0.004452,0.495689,
-0.714873,-0.004468,0.495696,
-0.714865,-0.004468,0.495707,
-0.714861,-0.004468,0.495712,
1.149376,0.535507,-0.850007,
1.148299,0.522644,-0.858950,
1.131896,0.548370,-0.866402,
1.141174,0.548370,-0.853732,
1.139022,0.522644,-0.871620,
1.130820,0.535507,-0.875345,
-0.714856,-0.004452,0.495720,
-0.714865,-0.004468,0.495707,
-0.714861,-0.004468,0.495712,
-0.714859,-0.004440,0.495715,
-0.714877,-0.004446,0.495692,
-0.714873,-0.004468,0.495696,
-0.714878,-0.004452,0.495689,
-0.714873,-0.004435,0.495696,
-0.714861,-0.004435,0.495712,
0.298025,0.560908,0.376701,
0.318625,0.518300,0.415382,
0.725243,0.452142,0.054356,
0.744150,0.413037,0.089857,
0.408764,0.495497,0.345570,
0.496444,0.473548,0.278059,
0.581605,0.452474,0.212903,
0.664191,0.432298,0.150154,
0.644937,0.472122,0.113999,
0.562007,0.493010,0.176103,
0.476507,0.514784,0.240623,
0.388492,0.537425,0.307507
};
float my_vertices[] = {
-10,10,0,
-9.8,9.8,1.98997,
-9.6,9.6,2.8,
-9.4,9.4,3.41174,
-9.2,9.2,3.91918,
-9,9,4.3589,
-8.8,8.8,4.74974,
-8.6,8.6,5.10294,
-8.4,8.4,5.42586,
-8.2,8.2,5.72364,
-8,8,6,
-7.8,7.8,6.2578,
-7.6,7.6,6.49923,
-7.4,7.4,6.72607,
-7.2,7.2,6.93974,
-7,7,7.14143,
-6.8,6.8,7.33212,
-6.6,6.6,7.51266,
-6.4,6.4,7.68375,
-6.2,6.2,7.84602,
-6,6,8,
-5.8,5.8,8.14616,
-5.6,5.6,8.28493,
-5.4,5.4,8.41665,
-5.2,5.2,8.54166,
-5,5,8.66025,
-4.8,4.8,8.77268,
-4.6,4.6,8.87919,
-4.4,4.4,8.97998,
-4.2,4.2,9.07524,
-4,4,9.16515,
-3.8,3.8,9.24986,
-3.6,3.6,9.32952,
-3.4,3.4,9.40425,
-3.2,3.2,9.47418,
-3,3,9.53939,
-2.8,2.8,9.6,
-2.6,2.6,9.65609,
-2.4,2.4,9.70773,
-2.2,2.2,9.755,
-2,2,9.79796,
-1.8,1.8,9.83667,
-1.6,1.6,9.87117,
-1.4,1.4,9.90152,
-1.2,1.2,9.92774,
-1,1,9.94987,
-0.8,0.8,9.96795,
-0.6,0.6,9.98198,
-0.4,0.4,9.992,
-0.2,0.2,9.998,
-2.05391e-015,2.05391e-015,10,
0.2,0.2,9.998,
0.4,0.4,9.992,
0.6,0.6,9.98198,
0.8,0.8,9.96795,
1,1,9.94987,
1.2,1.2,9.92774,
1.4,1.4,9.90152,
1.6,1.6,9.87117,
1.8,1.8,9.83667,
2,2,9.79796,
2.2,2.2,9.755,
2.4,2.4,9.70773,
2.6,2.6,9.65609,
2.8,2.8,9.6,
3,3,9.53939,
3.2,3.2,9.47418,
3.4,3.4,9.40425,
3.6,3.6,9.32952,
3.8,3.8,9.24986,
4,4,9.16515,
4.2,4.2,9.07524,
4.4,4.4,8.97998,
4.6,4.6,8.87919,
4.8,4.8,8.77268,
5,5,8.66025,
5.2,5.2,8.54166,
5.4,5.4,8.41665,
5.6,5.6,8.28493,
5.8,5.8,8.14616,
6,6,8,
6.2,6.2,7.84602,
6.4,6.4,7.68375,
6.6,6.6,7.51266,
6.8,6.8,7.33212,
7,7,7.14143,
7.2,7.2,6.93974,
7.4,7.4,6.72607,
7.6,7.6,6.49923,
7.8,7.8,6.2578,
8,8,6,
8.2,8.2,5.72364,
8.4,8.4,5.42586,
8.6,8.6,5.10294,
8.8,8.8,4.74974,
9,9,4.3589,
9.2,9.2,3.91918,
9.4,9.4,3.41174,
9.6,9.6,2.8,
9.8,9.8,1.98997,
10,10,3.26468e-007
};
float my_heart_vertices[] = {
-0.6,1.2,0,
-0.45,1.2,0,
-0.3,1.2,0,
0.3,1.2,0,
0.45,1.2,0,
0.6,1.2,0,
-1.05,0.9,0,
-0.9,0.9,0,
-0.75,0.9,0,
-0.6,0.9,0,
-0.45,0.9,0,
-0.3,0.9,0,
-0.15,0.9,0,
-1.19209e-007,0.9,0,
0.15,0.9,0,
0.3,0.9,0,
0.45,0.9,0,
0.6,0.9,0,
0.75,0.9,0,
0.9,0.9,0,
1.05,0.9,0,
-1.05,0.6,0,
-0.9,0.6,0,
-0.75,0.6,0,
-0.6,0.6,0,
-0.45,0.6,0,
-0.3,0.6,0,
-0.15,0.6,0,
-1.19209e-007,0.6,0,
0.15,0.6,0,
0.3,0.6,0,
0.45,0.6,0,
0.6,0.6,0,
0.75,0.6,0,
0.9,0.6,0,
1.05,0.6,0,
-1.05,0.3,0,
-0.9,0.3,0,
-0.75,0.3,0,
-0.6,0.3,0,
-0.45,0.3,0,
-0.3,0.3,0,
-0.15,0.3,0,
-1.19209e-007,0.3,0,
0.15,0.3,0,
0.3,0.3,0,
0.45,0.3,0,
0.6,0.3,0,
0.75,0.3,0,
0.9,0.3,0,
1.05,0.3,0,
-0.9,0,0,
-0.75,0,0,
-0.6,0,0,
-0.45,0,0,
-0.3,0,0,
-0.15,0,0,
-1.19209e-007,0,0,
0.15,0,0,
0.3,0,0,
0.45,0,0,
0.6,0,0,
0.75,0,0,
0.9,0,0,
-0.75,-0.3,0,
-0.6,-0.3,0,
-0.45,-0.3,0,
-0.3,-0.3,0,
-0.15,-0.3,0,
-1.19209e-007,-0.3,0,
0.15,-0.3,0,
0.3,-0.3,0,
0.45,-0.3,0,
0.6,-0.3,0,
0.75,-0.3,0,
-0.45,-0.6,0,
-0.3,-0.6,0,
-0.15,-0.6,0,
-1.19209e-007,-0.6,0,
0.15,-0.6,0,
0.3,-0.6,0,
0.45,-0.6,0,
-1.19209e-007,-0.9,0
};
float* vertices_arr[] = { nullptr, nullptr, diamond_vertices, heart_vertices, bird_vertices, my_vertices, my_heart_vertices};
int vertices_num[] = { 0, 0, 198 / 3, 276 / 3, 1104 / 3, 303 / 3, 249/3};
//int vertices_num[] = { 0, 0, 317 / 3, 500 / 3, 2000 / 3 };
#endif