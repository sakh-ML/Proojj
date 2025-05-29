library ieee;
use ieee.std_logic_1164.all;

entity negierer_tb is
end negierer_tb;

architecture testbench of negierer_tb is

-- die zu testende Komponente
  component negierer
    port (
        input : IN std_logic_vector(1 DOWNTO 0);
        output : OUT std_logic_vector(1 DOWNTO 0)
    );
  end component;

-- Eingabe und Ausgabe der Testbench
signal  input : std_logic_vector(1 DOWNTO 0);
signal  output   : std_logic_vector(1 DOWNTO 0);
begin

    -- Die Komponente wird verschaltet
    neg: negierer port map(input => input, output => output);
    -- im GTKWave kann man sich die beiden not_gate_assignments not_gate_assignment(0) und not_gate_assignment(1) getrennt ansehen
    process begin
        -- die verschiedenen Eingaben werden durchgegangen
        input <= "00";
        wait for 10 ns;
        input <= "01";
        wait for 10 ns;
        input <= "10";
        wait for 10 ns;
        input <= "11";
        wait for 10 ns;

        wait;
    end process;
end testbench;
