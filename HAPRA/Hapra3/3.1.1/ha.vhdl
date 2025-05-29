library ieee;
use ieee.std_logic_1164.all;

-- Halbaddierer / Halfadder

entity ha is
  port (
    a: in std_logic;
    b: in std_logic;
    s: out std_logic;
    c: out std_logic
  );
end ha;

architecture rtl of ha is
begin
 
 -- hier sind die zwei outpu (c,s)
    c <= a and b;
    s <= a xor b;

end rtl;
