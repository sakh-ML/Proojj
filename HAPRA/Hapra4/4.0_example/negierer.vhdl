LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;

-- Der einfache Negierer bekommt einen Vector mit 2 Bits übergeben und negiert den Vector bitweise
ENTITY negierer IS
    PORT (
        input : IN std_logic_vector(1 DOWNTO 0);
        output : OUT std_logic_vector(1 DOWNTO 0)
        );
END negierer;

ARCHITECTURE rtl OF negierer IS
    -- er wird aus not_gates gebaut
    COMPONENT not_gate IS
        port (
          input1 : in std_logic;
          not_output : out std_logic
        );
    END COMPONENT;

BEGIN
    -- es werden 2 not_gates erzeugt die jeweils die einzlen Bits negieren. Dabei wird mit input(i) bzw output(i) das Bit an Stelle i gelesen bzw gesetzt
    not_gate_assignment : for i in 0 to 1 generate
        not_output: not_gate port map (input1 => input(i), not_output => output(i));
    end generate not_gate_assignment;

END rtl;
