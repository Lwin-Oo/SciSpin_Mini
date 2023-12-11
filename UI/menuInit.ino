void menuInit(){

 unsigned int i = 0;
//_______________ First Layer _______________//
 menu[i].code = 0;
 menu[i++].text = "EMERGENCY STOP";
 menu[i].code = 1;
 menu[i++].text = "MOTOR CONTROL";
 menu[i].code = 2;
 menu[i++].text = "LED CONTROL";
 menu[i].code = 3;
 menu[i++].text = "RESET";
 menu[i].code = 4;
 menu[i++].text = "SAVE SETTINGS";

//_______________ Second Layer _______________//

//1: "MOTOR CONTROL"//
 menu[i].code = 10;
 menu[i++].text = "RETURN";
 menu[i].code = 11;
 menu[i++].text = "SET INTERVAL";
 menu[i].code = 12;
 menu[i++].text = "TOGGLE MOTOR";
 menu[i].code = 13;
 menu[i++].text = "REVERSE DIR";
 menu[i].code = 14;
 menu[i++].text = "SET MICROSTEPS";

//2: "LED CONTROL"//
 menu[i].code = 20;
 menu[i++].text = "RETURN";
 menu[i].code = 21;
 menu[i++].text = "TOGGLE LIGHTS";
 menu[i].code = 22;
 menu[i++].text = "SET COLOR";
 menu[i].code = 23;
 menu[i++].text = "SET INTENSITY";


//_______________ Third Layer _______________//

//1: "MOTOR CONTROL"//
 menu[i].code = 110;
 menu[i++].text = "INTERVALS:";
 menu[i].code = 140;
 menu[i++].text = "MICROSTEPS:";

//2: "LED CONTROL"//
 menu[i].code = 220;
 menu[i++].text = "RETURN";
 menu[i].code = 221;
 menu[i++].text = "RED";
 menu[i].code = 222;
 menu[i++].text = "GREEN";
 menu[i].code = 223;
 menu[i++].text = "BLUE";
 menu[i].code = 224;
 menu[i++].text = "WARM WHITE";

//_______________ Fourth Layer _______________// 

//2: "LED CONTROL"//
 menu[i].code = 2210;
 menu[i++].text = "RED";
 menu[i].code = 2220;
 menu[i++].text = "GREEN";
 menu[i].code = 2230;
 menu[i++].text = "BLUE";

 maxMenuItems = i + 1;

 readSettings();
}
