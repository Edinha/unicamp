from mininet.topo import Topo

class Dumbell( Topo ):
    "Simple dumbell topology"

    def __init__( self ):
        "Create custom topo."

        # Initialize topology
        Topo.__init__( self )

        # Add hosts and switches
        topLeftHost = self.addHost( 'h1' )
        topRightHost = self.addHost( 'h2' )
        bottomLeftHost = self.addHost( 'h3' )
        bottomRightHost = self.addHost( 'h3' )
        leftSwitch = self.addSwitch( 's3' )
        rightSwitch = self.addSwitch( 's4' )

        # Add links
        self.addLink( topLeftHost, leftSwitch )
        self.addLink( bottomLeftHost, leftSwitch )

        self.addLink( topRightHost, rightSwitch )
        self.addLink( bottomRightHost, rightSwitch )

        self.addLink( leftSwitch, rightSwitch )

topos = { 'dumbell': ( lambda: Dumbell() ) }
