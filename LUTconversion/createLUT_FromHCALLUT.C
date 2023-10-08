#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int fiberToIdet(int fiber, int fibchan); 
int hexToDecimal(char hexadecimalnumber[30]);

void createLUT_FromHCALLUT(int capid = 0) {
  // side=0 -> Negative: NEM1, NEM2, NEM3, NEM4, NEM5, NHD1, NHD2, NHD3, NHD4,
  // side=1 -> Positive: PEM1, PEM2, PEM3, PEM4, PEM5, PHD1, PHD2, PHD3, PHD4
  // read in XML file
  std::string xmlfile = "ZDC_pedestalWitdthTest.xml";
  std::ifstream infile(xmlfile.c_str());
  if( !infile ){
    std::cout << "[Error]: Can't open " << xmlfile.c_str() << std::endl;
    exit(-1);
  }
  std::string line = "";

  bool doOOTPU = true; 
  bool doDebug = false;

  if(doDebug)std::cout << "Reading XML file " << xmlfile << std::endl;
  // read in calibration constants
  double QIE10_regular_fC_full[256][18]; // [ibit][idet]
  int zdcLines = 0;
  int zdcPlines = 0; 
  int zdcMlines = 0;
  int channel = 0; 
  int zside = 0;
  int iPHI = 0; 
  int iFIBER = 0;
  int iFIBERCHAN = 0;
  int idet = 0;
  while (std::getline(infile, line)) {
    // initialize the variables we need 
    if(doDebug)std::cout << line << std::endl;
    if (line.find("<CFGBrick>") != std::string::npos){
      iPHI = 0;
      iFIBER = 0;
      iFIBERCHAN = 0;
    }

    // line is of the format  <Parameter name="IPHI" type="int">63</Parameter>
    if(line.find("<Parameter name=\"IPHI\" type=\"int\">") != std::string::npos){
      int pos = 38; 
      std::string phi = line.substr(pos, 1);
      while (line.substr(pos+1, 1) != "<") {
        std::string newline = line.substr(pos+1, 1);
        phi = phi + newline;
        pos = pos + 1;
      }
      iPHI = std::stoi(phi);
    }
    else if(line.find("<Parameter name=\"FIBER\" type=\"int\">") != std::string::npos){
      int pos = 39; 
      std::string fib = line.substr(pos, 1);
      while (line.substr(pos+1, 1) != "<") {
        std::string newline = line.substr(pos+1, 1);
        fib = fib + newline;
        pos = pos + 1;
      }

      iFIBER = std::stoi(fib);
    }
    else if(line.find("<Parameter name=\"FIBERCHAN\" type=\"int\">") != std::string::npos){
      int pos = 43; 
      std::string fibchan = line.substr(pos, 1);
      while (line.substr(pos+1, 1) != "<") {
        std::string newline = line.substr(pos+1, 1);
        fibchan = fibchan + newline;
        pos = pos + 1;
      }

      iFIBERCHAN = std::stoi(fibchan);
    }
    // line format
    else if (line.find("<Data elements=\"256\" encoding=\"hex\">") != std::string::npos){
      if(iPHI == -1000){
        int idet = fiberToIdet(iFIBER, iFIBERCHAN);
        if (idet != -1){
	  if(doDebug){
	    std::cout << "------- starting new entry --------" << std::endl;
	    std::cout << "found the zdc " << line << std::endl;
	    std::cout << " fiber " << iFIBER << std::endl;
	    std::cout << " fiberchan " << iFIBERCHAN << std::endl;
	    std::cout << " idet = " << idet << std::endl;
	  }
          zdcLines = zdcLines + 1;
          //std::cout << "--------------------------" << std::endl;
          int globalpos = 40; 
          int index = 0; 
          //std::string inithex = line.substr(globalpos, 1);
          while (line.substr(globalpos+1, 1) != "<") {
            std::string hex = line.substr(globalpos, 1);
            while (line.substr(globalpos+1, 1) != " ") {
              hex = hex +  line.substr(globalpos+1, 1);
              globalpos = globalpos + 1;
            }
            globalpos = globalpos + 1;
            unsigned int decimal;   
            std::stringstream ss;
            ss << std::hex << hex;
            ss >> decimal;
	    if(doOOTPU){
	      if(iFIBER == 6 || iFIBER == 7 || iFIBER == 8 || iFIBER == 18 || iFIBER == 19 || iFIBER == 20){
		QIE10_regular_fC_full[index][idet] = decimal;
	      }
	    }
	    else{
	      if(iFIBER == 0 || iFIBER == 1 || iFIBER == 2 || iFIBER == 12 || iFIBER == 13 || iFIBER == 14){
		QIE10_regular_fC_full[index][idet] = decimal;
	      }
	    }
            if(doDebug)std::cout << "index " << index << " decimal " << decimal << " "; 
            index = index + 1;
          }
        }
      } 
    }
  }

 



  //Flattened output
  const double scalingFactor = 1.0;
  std::cout << std::endl;
  //std::cout << "# ZDC LUT for HI running 2023, Dummy Implementation (always return 1)" << std::endl;
  std::cout << "# ZDC LUT for HI running 2023, commissioning implementation" << std::endl;
  std::cout << "# Scaling factor of " << (int)scalingFactor << " used for double -> int conversion" << std::endl;
  std::cout << "#<header> V1 13 32 </header>" << std::endl;
  std::cout << std::endl;

  int index = 0;
  //Dump the scaling factor first for instant retrieval
  std::cout << index << " " << (int)scalingFactor << " # Scaling Factor" << std::endl;
  ++index;
  for (int idet = 0; idet < 18; idet++) {
    for (int ibit = 0; ibit < 256; ibit++) {
      if(idet < 5){
	std::cout << index << " " << 0 << " # [index ibit=" << ibit << "], [index idet=" << idet << "]" << std::endl;
      }
      else if(idet > 4  && idet < 9 ){
	std::cout << index << " " << (int)(QIE10_regular_fC_full[ibit][idet]*scalingFactor) << " # [index ibit=" << ibit << "], [index idet=" << idet << "]" << std::endl;
      }
      else if(idet > 8 && idet < 14){
	std::cout << index << " " << 0 << " # [index ibit=" << ibit << "], [index idet=" << idet << "]" << std::endl;
      }
      else{
	std::cout << index << " " << (int)(QIE10_regular_fC_full[ibit][idet]*scalingFactor) << " # [index ibit=" << ibit << "], [index idet=" << idet << "]" << std::endl;
      }
      ++index;
    }
  }

  return;
}

int hexToDecimal(char hexadecimalnumber[30]= "2D"){

 int decimalNumber = 0;
    
    // Storing hexa number digits in one array
    char hexDigits[16] = { '0', '1', '2', '3', '4', '5', '6', '7',
                           '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    int i, j, power = 0, digit;
  
    // Converting hexadecimal number to equivalent decimal
    // number
    for (i = strlen(hexadecimalnumber) - 1; i >= 0; i--) {
  
        // search if given input character is present in the
        // array or not. if it present in the array then
        // find the equivalent decimal number for each hexa
        // digit
        for (j = 0; j < 16; j++) {
            if (hexadecimalnumber[i] == hexDigits[j]) {
                decimalNumber += j * pow(16, power);
            }
        }
        power++;
    }
  return decimalNumber;

}


int fiberToIdet(int fiber, int fibchan){
  int zside = 0;
  int channel = 0; 
  int section = 0; 
  if((fiber == 6 && fibchan == 0) || (fiber == 0 && fibchan == 0)){
    zside = -1; 
    channel = 1;
    section = 1;
  }
  else if ((fiber == 6 && fibchan == 1) || (fiber == 0 && fibchan == 1)){
    zside = -1;
    channel = 2;
    section = 1;
  }
  else if((fiber == 6 && fibchan == 2) || (fiber == 0 && fibchan == 2)){
    zside = -1; 
    channel = 3;
    section = 1;
  }
  else if ((fiber == 6 && fibchan == 3) || (fiber == 0 && fibchan == 3)){
    zside = -1;
    channel = 4;
    section = 1;
  }
  else if ((fiber == 7 && fibchan == 0) || (fiber == 1 && fibchan == 0)){
    zside = -1; 
    channel = 5;
    section = 1;
  }
  else if((fiber == 7 && fibchan == 1) || (fiber == 1 && fibchan == 1)){
    zside = -1; 
    channel = 1; 
    section = 2;
  }
  else if((fiber == 7 && fibchan == 2) || (fiber == 1 && fibchan == 2)){
    zside = -1; 
    channel = 2; 
    section = 2;
  }
  else if((fiber == 7 && fibchan == 3) || (fiber == 1 && fibchan == 3)){
    zside = -1; 
    channel = 3; 
    section = 2;
  }
  else if((fiber == 8 && fibchan == 0) || (fiber == 2 && fibchan == 0)){
    zside = -1; 
    channel = 4; 
    section = 2;
  }
  else if((fiber == 18 && fibchan == 0) || (fiber == 12 && fibchan == 0)){
    zside = 1; 
    channel = 1; 
    section = 1;
  }
  else if((fiber == 18 && fibchan == 1)  || (fiber == 12 && fibchan == 1)){
    zside = 1; 
    channel = 2; 
    section = 1;
  }
  else if((fiber == 18 && fibchan == 2) || (fiber == 12 && fibchan == 2)){
    zside = 1; 
    channel = 3; 
    section = 1;
  }
  else if((fiber == 18 && fibchan == 3) || (fiber == 12 && fibchan == 3)){
    zside = 1; 
    channel = 4; 
    section = 1;
  }
  else if((fiber == 19 && fibchan == 0) || (fiber == 13 && fibchan == 0)){
    zside = 1; 
    channel = 5; 
    section = 1;
  }
  else if((fiber == 19 && fibchan == 1) || (fiber == 13 && fibchan == 1)){
    zside = 1; 
    channel = 1; 
    section = 2;
  }
  else if((fiber == 19 && fibchan == 2) || (fiber == 13 && fibchan == 2)){
    zside = 1; 
    channel = 2; 
    section = 2;
  }
  else if((fiber == 19 && fibchan == 3) || (fiber == 13 && fibchan == 3)){
    zside = 1; 
    channel = 3; 
    section = 2;
  }
  else if((fiber == 20 && fibchan == 0) || (fiber == 14 && fibchan == 0)){
    zside = 1; 
    channel = 4; 
    section = 2;
  }
  else{
    std::cout << "ERROR: fiber = " << fiber << " fiberchan = " << fibchan << " not recognized." << std::endl;
  }  
  int ihitid = (zside == 1 ? 9 : 0) + (section == 2 ? 5 : 0) + (channel - 1);
  std::cout << ihitid << std::endl;
  return ihitid;
}

