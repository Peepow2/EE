function y = f(x, A, B)
    a = A(1); b = A(2); 
    c = B(1); d = B(2);
    %{ % Alternative
    y = x
    result(y >= 0 & y < a)  = (c/a) * result(y >= 0 & y < a);
    result(y >= a & y < b)  = ((d-c)/(b-a)) * result(y >= a & y < b)  + (c - (((d-c)/(b-a))*a));
    result(y >= b & y <= 1) = ((1-d)/(1-b)) * result(y >= b & y <= 1) + (d - (((1-d)/(1-b))*b));
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
