library ieee;
use ieee.std_logic_1164.all;
--hier benutzen wir die clag und facla datei, die wir schon implemntiert haben
use WORK.clag;
use WORK.facla;

entity cla is
  port (
    a    : in std_logic_vector(3 downto 0);
    b    : in std_logic_vector(3 downto 0);
    cin  : in std_logic;
    cout : out std_logic;
    sum  : out std_logic_vector(3 downto 0)
  );
end cla;

architecture rtl of cla is
-- hier ist die facla port
  component facla is
    port (
      a    : in std_logic;
      b    : in std_logic;
      cin  : in std_logic;
      g    : out std_logic;
      p    : out std_logic;
      sum  : out std_logic
    );
  end component facla;
--hier ist die clag port
  component clag is
    port (
      gin  : in std_logic_vector(3 downto 0);
      pin  : in std_logic_vector(3 downto 0);
      cin  : in std_logic;
      cout : out std_logic_vector(3 downto 0);
      pout : out std_logic;
      gout : out std_logic
    );
  end component clag;

  --hier sind alle signale die wir brauchen
  signal g, p : std_logic_vector(3 downto 0);
  signal c    : std_logic_vector(3 downto 0);
  signal pout_internal : std_logic; 

begin
  
--hier ist einmal die clag
  U0: clag
    port map(
      gin  => g,
      pin  => p,
      cin  => cin,
      cout => c,
      pout => pout_internal,  
      gout => cout
    );

 -- und hier sind the facla 4 mal !, jedes mal nehmen wir das neue bit mit dem altes cout. 
  U1: facla
    port map(
      a    => a(0),
      b    => b(0),
      cin  => cin,
      g    => g(0),
      p    => p(0),
      sum  => sum(0)
    );

  U2: facla
    port map(
      a    => a(1),
      b    => b(1),
      cin  => c(0),
      g    => g(1),
      p    => p(1),
      sum  => sum(1)
    );

  U3: facla
    port map(
      a    => a(2),
      b    => b(2),
      cin  => c(1),
      g    => g(2),
      p    => p(2),
      sum  => sum(2)
    );

  U4: facla
    port map(
      a    => a(3),
      b    => b(3),
      cin  => c(2),
      g    => g(3),
      p    => p(3),
      sum  => sum(3)
    );

end rtl;

