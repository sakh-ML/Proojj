library ieee;
use ieee.std_logic_1164.all;

entity clag is
  port (
    gin : in std_logic_vector(3 downto 0);
    pin : in std_logic_vector(3 downto 0);
    cin : in std_logic;
    cout : out std_logic_vector(3 downto 0);
    pout : out std_logic;
    gout : out std_logic
  );
end clag;

architecture rtl of clag is

-- hier sind alle signals

 signal wire_1 : std_logic;
 signal wire_2 : std_logic;
 signal wire_3 : std_logic;
 signal wire_4 : std_logic;
 
begin
    
-- hier sind alle outputs

    gout <= gin(3) or (pin(3) and gin(2)) or (pin(3) and pin(2) and gin(1)) or (pin(3) and pin(2) and pin(1) and gin(0));
    
    pout <= pin(3) and pin(2) and pin(1) and pin(0);
    
    cout(0) <= gin(0) or (pin(0) and cin);
    
    cout(1) <= gin(1) or (pin(1) and gin(0)) or (pin(1) and pin(0) and cin);
    
    cout(2) <= gin(2) or (pin(2) and gin(1)) or (pin(2) and pin(1) and gin(0)) or (pin(2) and pin(1) and pin(0) and cin);
    
    cout(3) <= gin(3) or (pin(3) and gin(2)) or (pin(3) and pin(2) and gin(1)) or (pin(3) and pin(2) and pin(1) and gin(0)) or (pin(3) and pin(2) and pin(1) and pin(0) and cin);

  
end rtl;
