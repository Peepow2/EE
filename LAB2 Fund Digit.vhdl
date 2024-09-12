--- Problem 1 (7 sep 2024) ---
--- Prove the validity of the logic equation (A + C)(AB + C') = AB + AC'

--- Group Name # 25
--- Yotsapat  Suparanonrat 6530336521
--- Ratchapol Kaisuwan     6530344521
--- Peerawich Sodsuay      6530295421

entity LAB2_1 is 
    port (
        A, B, C : in bit; --- A, B, C are input variables.
        D, E  	 : out bit --- D, E are output variables.
    );
end LAB2_1;

architecture behavior of LAB2_1 is --- Project Name
begin
    --- D = (A + C)(AB + C')
    D <= (A or C) and ((A and B) or not C);
    --- E = AB + AC'
	 E <= (A and B) or (A and (not C));
end behavior;


--- Problem 2 (7 sep 2024) ---
--- Prove the validity of the logic equation ABC + AB'(A'C')' = A(C + B')

--- Group Name # 25
--- Yotsapat  Suparanonrat 6530336521
--- Ratchapol Kaisuwan     6530344521
--- Peerawich Sodsuay      6530295421

entity LAB2_2 is
    port (
        A, B, C : in bit; --- A, B, C are input variables.
        D, E  	 : out bit --- D, E are output variables.
    );
end LAB2_2;

architecture behavior of LAB2_2 is --- Project Name
begin
    --- D = ABC + AB'(A'C')'
    D <= (A and B and C) or (A and (not B)) and (not(not A and not C));
    --- E = A(C + B')
	E <= A and (C or not B);
end behavior;


--- Problem 3 (7 sep 2024) ---
--- Given Z = s'A + sB, then show that Z = A when s = 0 and Z = B when s = 1

--- Group Name # 25
--- Yotsapat  Suparanonrat 6530336521
--- Ratchapol Kaisuwan     6530344521
--- Peerawich Sodsuay      6530295421

entity LAB2_3 is
    port (
        A, B, s : in bit; --- A, B, s are input variables.
        Z       : out bit --- Z is output variable.
    );
end LAB2_3;

architecture behavior of LAB2_3 is --- Project Name
begin
    --- Z = s'A + sB
    Z = (not s and A) or (s and B);
end behavior;
