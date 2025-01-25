function y = f(x, A, B)
    a = A(1); b = A(2); 
    c = B(1); d = B(2);
    
    %{ % Alternative
    y = x;
    y(x >= 0 & x < a)  = (c/a) * y(x >= 0 & x < a);

    y(x >= a & x < b)  = ((d-c)/(b-a)) * y(x >= a & x < b) ...
                                + (c - (((d-c)/(b-a))*a));

    y(x >= b & x <= 1) = ((1-d)/(1-b)) * y(x >= b & x <= 1) ...
                                + (d - (((1-d)/(1-b))*b));
    }%
    
    % For 0 <= x < a (First interval)
    if (x >= 0) && (x < a)
        y = (c/a)*x;
    
    % For a <= x < b (Second interval)
    elseif (x >= a) && (x < b)
        y = ((d-c)/(b-a))*x + c - (((d-c)/(b-a))*a);
    
    % For b <= x < 1 (Third interval)
    elseif (x >= b) && (x <= 1)
        y = ((1-d)/(1-b))*x + d - (((1-d)/(1-b))*b);
    
    % Another case
    else
        y = 0;
    end
end

a = 0.30; b = 0.70; c = 0.20; d = 0.85;
f(0.2, [a b], [c d])
