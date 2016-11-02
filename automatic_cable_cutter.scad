forwarder_wheel_radius =35;
forwarder_wheel_axis_radius =4;
forwarder_wheel_height =50;
forwarder_wheel_space =0.4;
//projection() translate([0,0,45])rotate([0,90,0])	
//	translate([50,41,4])rotate([0,-90,-180])cutblock();

//translate([100,0,0]){
//	gear();
//	translate([25,0,0])gearcutter();
//}

//projection() translate([0,0,83])rotate([0,90,0])	
//rotate([90,0,0])forwarder();


forwarderFront();
translate([25,0,0])forwarderBack();


//funnelblock();

module forwarderFront(){
	difference(){
		rotate([90,0,0])forwarder();
		translate([-100,-90,0])cube([100,100,100]);
	}
}
module forwarderBack(){
	difference(){
		rotate([90,0,0])forwarder();
		translate([0,-90,0])cube([100,100,100]);
	}
}

module funnelblock(){
	scale([1,0.5,1]){
		
		difference(){
			union(){
				difference(){
					union(){
						translate([0,0,0])cylinder(h=50,r=20);
						translate([0,0,0])rotate([0,90,0])cylinder(h=50,r=20);
						translate([50,0,0])rotate([0,0,0])cylinder(h=50,r=20);
						translate([0,0,50])rotate([0,90,0])cylinder(h=50,r=20);
					}
					translate([30.25,-30,19.75])rotate([0,0,90])aluguide();
					translate([-25,0,-25])cube([100,100,100]);
					translate([-25,-25,-25])cube([25,100,100]);
					translate([50,-25,-25])cube([25,100,100]);
					translate([-25,-25,-25])cube([100,100,25]);
					translate([-25,-25,50])cube([100,100,25]);
				}
				
//			translate([-10,-20,-10])cube([10,20,70]);
//			translate([50,-20,-10])cube([10,20,70]);
//			translate([-10,-20,-10])cube([70,20,10]);
//			translate([-10,-20,50])cube([70,20,10]);
			}
			translate([10,23,10]){
				translate([0,0,0])rotate([90,0,0])m3Screw( 30,14);
				translate([30,0,0])rotate([90,0,0])m3Screw(30,14);
				translate([30,0,30])rotate([90,0,0])m3Screw(30,14);
				translate([0,0,30])rotate([90,0,0])m3Screw(30,14);
			}
		}
	}
		
	
		
	
}

module cutblock(){
	mirror([1,0,0])difference(){
		translate([0,-10,0])cube([45,45,15]);
		translate([0,-12,5.4])cube([35,54,1]);
		translate([6,-10,6])cube([10,20,100]);
		translate([6,6,50])rotate([0,90,0])aluguide();
		translate([8,-3,-0.2])nutslotm3(24,25);
//		translate([4,8,-0.2])rotate([0,0,90])nutslotm3(6);
		translate([40,6,-10])rotate([0,0,0])m3Screw(20);
		translate([40,28,-10])rotate([0,0,0])m3Screw(20);
	}
}

module forwarder(){
	difference(){
			union(){
				
				translate([-45,13,1])cube([90,32,30]);
				translate([25,13,1])cube([30,32,30]);
				translate([0,3,0])hull(){
			     translate([-45,10,31])cube([90,15,4]);
				translate([26,20,60])rotate([90,0,0])cylinder(h=10,r=9);
				translate([-29,20,60])rotate([90,0,0])cylinder(h=10,r=9);
				
				}
			}
		translate([-22,0,31])cube([80,50,50]);//save material and time
		translate([-15,0,-18])cube([30,50,50]);//save material and time
		translate([0,-7.5,-2]) {
			translate([0,0,-20])cylinder(h=forwarder_wheel_height+(forwarder_wheel_space),r=forwarder_wheel_radius+forwarder_wheel_space);
			translate([0,0,0])cylinder(h=50,r=30);//gear
			translate([0,70,-20])cylinder(h=forwarder_wheel_height+(forwarder_wheel_space),r=forwarder_wheel_radius+forwarder_wheel_space);
			translate([0,70,0])cylinder(h=100,r=forwarder_wheel_axis_radius);
			translate([0,0,0])cylinder(h=100,r=forwarder_wheel_axis_radius);
		}
		#translate([0,-0.5,-1.5]){
			translate([34,25,10])aluguidefunnel();
			translate([-50,25,10])aluguide();
		}
//		translate([37,22,60])rotate([0,0,-90])nutslotm5();
//		translate([37,46,60])rotate([0,0,-90])nutslotm5();
		
		#translate([-40,27,7])rotate([90,180,180])nutslotm3();
		#translate([50,37,16.5])rotate([180,0,180])nutslotm3();
		translate([25,-4,60])rotate([-90,0,0])m5Screw(25);
		translate([-30,-4,60])rotate([-90,0,0])m5Screw(25);
}
	
}


module aluguide(){
	cube([100,10.4,10.4]);
}
module aluguidefunnel(){
	union(){
		cube([50,10.4,10.4]);
		hull(){
			translate([5,0,0])cube([1,10.4,10.4]);
			translate([-20,-2.5,-2.5])cube([1,15,15]);
		}
}
}
module gear(){
	difference(){
		union(){
			linear_extrude(height = 7, center = true, convexity = 10) import (file = "/home/simon/gearsmall.dxf", layer = "Ebene_1");
			translate([0,0,3.5])cylinder(h=7,r=9);
		}
		translate([0,0,-50])cylinder(h=100,r=3.2);
		translate([-3,4,3])union(){
			cube([6,2,100]);
			translate([3,5,3])rotate([0,90,90])cylinder(h=20,r=2,center=true);
		}
	}
		
}

module gearcutter(){
	difference(){
		union(){
			linear_extrude(height = 7, center = true, convexity = 10) import (file = "/home/simon/gearsmallcutter.dxf", layer = "Ebene_1");
			translate([0,0,3.5])cylinder(h=7,r=9);
		}
		translate([0,0,-50])cylinder(h=100,r=3.2);
		translate([-3,4,3])union(){
			cube([6,2,100]);
			translate([3,5,3])rotate([0,90,90])cylinder(h=20,r=2,center=true);
		}
	}
		
}

module nutslotm3(sh=100,scl=20){
	union(){
		cube([6,2,sh]);
		translate([3,5,3])rotate([0,90,90])cylinder(h=scl,r=2,center=true);
	}
}

module nutslotm5(slh=100,sl=50){
	union(){
		cube([8,3,slh]);
		translate([4,15,4])rotate([0,90,90])cylinder(h=sl,r=2.6,center=true);
	}
}

module m5Screw(h=10) {
	union() {
		cylinder(h=h,r=2.8);
		translate([0,0,h])cylinder(h=20,r=5);
	}
}

module m3Screw(h=15,hh=5.5) {
	union() {
		translate([0,0,5])cylinder(h=h+5,r=3.6/2);
// cylinder(h=5,r=3.6/2);
		translate([0,0,h-0.4])cylinder(h=hh,r=6.3/2);
		translate([0,0,-0.1])cylinder(h=5.5,r=6.9/2,$fn=6);
	}
}

