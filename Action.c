Action()
{

	int j;
	int ostatok;
	char* z;
	int cost[4];
	char* costFull[4];	

	web_reg_save_param_ex(
		"ParamName=SeatingPref",
		"LB=seatPref\" value=\"",
		"RB=\"",
		"Ordinal={Random3}",
		SEARCH_FILTERS,
		LAST);
	
	web_reg_save_param_ex(
		"ParamName=TypeofSeat",
		"LB=seatType\" value=\"",
		"RB=\"",
		"Ordinal={Random4}",
		SEARCH_FILTERS,
		LAST);
	
	web_url("Search Flights Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);
	
	web_reg_save_param_ex(
		"ParamName=CostFull",
		"LB=\"outboundFlight\" value=\"",
		"RB=\"",
		"Ordinal=All",
		SEARCH_FILTERS,
		LAST);
	
	web_reg_save_param_regexp(
		"ParamName=CostOut",
		"RegExp=\"outboundFlight\" value=\".{1,3};([0-9]*);",
		"Ordinal=All",
		SEARCH_FILTERS,
		LAST);
		
	web_submit_data("reservations.pl", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value={Discount}", ENDITEM, 
		"Name=depart", "Value={HomeCity}", ENDITEM, 
		"Name=departDate", "Value={DepartDate}", ENDITEM, 
		"Name=arrive", "Value={ArriveCity}", ENDITEM, 
		"Name=returnDate", "Value={ReturnDate}", ENDITEM, 
		"Name=numPassengers", "Value={NumberPassengers}", ENDITEM, 
		"Name=roundtrip", "Value=<OFF>", ENDITEM, 
		"Name=seatPref", "Value={SeatingPref}", ENDITEM, 
		"Name=seatType", "Value={TypeofSeat}", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		"Name=findFlights.x", "Value=65", ENDITEM, 
		"Name=findFlights.y", "Value=9", ENDITEM, 
		LAST);
	
		lr_output_message("Departure City: %s",lr_eval_string("{HomeCity}"));
		lr_output_message("Seating Preference: %s",lr_eval_string("{SeatingPref}"));
		lr_output_message("Type of Seat: %s",lr_eval_string("{TypeofSeat}"));
		lr_output_message("");
		
			
		z = lr_eval_string("{CostOut_1}");
		cost[0] = atoi(z);
		z = lr_eval_string("{CostOut_2}");
		cost[1] = atoi(z);
		z = lr_eval_string("{CostOut_3}");
		cost[2] = atoi(z);
		z = lr_eval_string("{CostOut_4}");
		cost[3] = atoi(z);
		
		costFull[0] = lr_eval_string("{CostFull_1}");
		costFull[1] = lr_eval_string("{CostFull_2}");
		costFull[2] = lr_eval_string("{CostFull_3}");
		costFull[3] = lr_eval_string("{CostFull_4}");
		
		
		for(j=0; j<4; j++) {
			
			ostatok = cost[j] % 2;
			
			lr_save_int(j, "step");
			lr_save_int(ostatok, "mod%2");
			lr_output_message("Step of cycle is: %s", lr_eval_string("{step}"));
			lr_output_message("Result of operation %2 is: %s", lr_eval_string("{mod%2}"));
			
			lr_save_string(costFull[j], "costFull");
			lr_output_message("Full cost on this step is: %s", lr_eval_string("{costFull}"));
			
		
			
			if (ostatok == 0) {
				
				web_submit_data("reservations.pl_2", 
				"Action=http://localhost:1080/cgi-bin/reservations.pl", 
				"Method=POST", 
				"TargetFrame=", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
				"Snapshot=t6.inf", 
				"Mode=HTML", 
				ITEMDATA, 
				"Name=outboundFlight", "Value={costFull}", ENDITEM, 
				"Name=numPassengers", "Value={NumberPassengers}", ENDITEM, 
				"Name=advanceDiscount", "Value={Discount}", ENDITEM, 
				"Name=seatType", "Value={TypeofSeat}", ENDITEM, 
				"Name=seatPref", "Value={SeatingPref}", ENDITEM, 
				"Name=reserveFlights.x", "Value=64", ENDITEM, 
				"Name=reserveFlights.y", "Value=3", ENDITEM, 
				LAST);
		
		
				web_submit_data("reservations.pl_3", 
				"Action=http://localhost:1080/cgi-bin/reservations.pl", 
				"Method=POST", 
				"TargetFrame=", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
				"Snapshot=t7.inf", 
				"Mode=HTML", 
				ITEMDATA, 
				"Name=firstName", "Value={FirstName}", ENDITEM, 
				"Name=lastName", "Value={LastName}", ENDITEM, 
				"Name=address1", "Value={StreetAddress}", ENDITEM, 
				"Name=address2", "Value={CityStateZip}", ENDITEM, 
				"Name=pass1", "Value={FullName}", ENDITEM, 
				"Name=creditCard", "Value={CreditCard}", ENDITEM, 
				"Name=expDate", "Value={ExpDateCard}", ENDITEM, 
				"Name=oldCCOption", "Value=", ENDITEM, 
				"Name=numPassengers", "Value={NumberPassengers}", ENDITEM, 
				"Name=seatType", "Value={TypeofSeat}", ENDITEM, 
				"Name=seatPref", "Value={SeatingPref}", ENDITEM, 
				"Name=outboundFlight", "Value={costFull}", ENDITEM, 
				"Name=advanceDiscount", "Value={Discount}", ENDITEM, 
				"Name=JSFormSubmit", "Value=off", ENDITEM, 
				"Name=.cgifields", "Value=saveCC", ENDITEM, 
				"Name=buyFlights.x", "Value=74", ENDITEM, 
				"Name=buyFlights.y", "Value=19", ENDITEM, 
				LAST);
				
				break;
			}
			
		}
		
	
	return 0;
}