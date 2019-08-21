module steeringControl(x1,x2,k1,k2,clock,temp,time,hyst_urgent_clock)
    output x1,x2;

    mode loc1
        begin
            ddt x1  = -0.1 * k1 * x1 + (1.0 - 0.1 * k2) * x2 + 0.1 * 0.25 * 1.0;
            ddt x2  = -k1 * x1 - k2 * x2 + 0.25 * 1.0;
            ddt k1  = 0.0;
            ddt k2  = 0.0;
            ddt clock  = 1.0;
            ddt temp  = 0.0;
            ddt hyst_urgent_clock  = 0.0;
        end

    mode loc2
        begin
            ddt x1  = 0.0;
            ddt x2  = 0.0;
            ddt k1  = 0.0;
            ddt k2  = 0.0;
            ddt clock  = 0.0;
            ddt temp  = 0.0;
            ddt hyst_urgent_clock  = 1.0;
        end
    initial begin
        set begin
            mode=
            clock == 0.0;
            x1 == 0.0;
            x2 == 0.0;
            k1 == 1.5;
            k2 == 0.6;
#            0.0 <= k1;
#            k1 <= 1.0;
#            0.0 <= k2;
#            k2 <= 1.0;
            temp == 0.0; 
            hyst_urgent_clock == 0.0;
        end
    end


endmodule