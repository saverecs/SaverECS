module steeringControl(v,u)
    output v;

    mode loc
        begin
        ddt v  = (-50/1000)*v + (1/1000)*u;
        end

    initial begin
        set begin
            mode == loc;
            v <= 81;
            v >= 79;
            u <= 500;
            u >= 498;
        end
    end
endmodule