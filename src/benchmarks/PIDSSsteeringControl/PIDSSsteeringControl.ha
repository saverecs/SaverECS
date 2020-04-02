module steeringControl(v,u,z)
    output v,z;

    mode loc
        begin
        ddt v  = (-50/1000)*v + (1/1000)*u;
        ddt z  = v - 10;
        end

    initial begin
        set begin
            mode == loc;
            v <= 80;
            v >= 50;
            z <= 70;
            z >= 40;
            u >= 450;
            u <= 500;
        end
    end
endmodule