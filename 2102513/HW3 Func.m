function y = f(x)
    % define value of a, b, c and d
    a = 0.30; b = 0.70; c = 0.20; d = 0.85; 
    
    % For 0 <= x < a (First interval)
    if (x >= 0) && (x < a)
        y = (c/a)*x;
    
    % For a <= x < b (Second interval)
    elseif (x >= a) && (x < b)
        y = ((d-c)/(b-a))*x + c - (((d-c)/(b-a))*a);
    
    % For b <= x < 1 (Third interval)
    elseif (x >= b) && (x < 1)
        y = ((1-d)/(1-b))*x + d - (((1-d)/(1-b))*b);
    
    % Another case
    else
        y = 0;
    end
end

y = f(0.2)
