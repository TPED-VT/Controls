import java.awt.*;  
import java.awt.event.*;
import java.awt.geom.Line2D;
import java.util.Timer;
import java.util.TimerTask;
import javax.swing.*;

/*
 * // -------------------------------------------------------------------------
/**
 *  HMI for Ride Engineering Competition Topspin
 *  all visuals for the ride. Visuals update every 1.538 seconds, which is
 *  1% of the ride cycle. 
 * 
 *  @author hjl44 
 *  @version Mar 4, 2025
 */

public class JavaHMI {
    public static void main(String[] agrs) {
        KeyAsButton a = new KeyAsButton();
    }
}

class KeyAsButton extends JFrame implements KeyListener {
    JButton1 classic;
    JButton1 advanced;
    JPanel panel;
    JPanel upper;
    JButton1 restraintStatus;
    JButton1 cyclePercent;
    JButton1 rideStatus;
    JButton1 reset;
    JPanel middle;
    JButton1 degree;
    JPanel rectangle;
    JPanel rectangle2;
    boolean isClassic;
    JButton1 indicator;
    JButton1 errorBox;
    JButton1 init;
    JButton1 auto;
    JButton1 maint;
    JButton1 off;
    Timer timer;
    JTextField password;
    JPanel popupPanel;
    JFrame popup;
    JPanel progressBarBase;
    JPanel progressBar;
    JButton direction;
    JButton cyclesRun;

    public native int getCyclePercent();
        HMI_BackE backEnd; 

    static {
        System.loadLibrary("HMI_BackE");
    }

    public KeyAsButton() {
        isClassic = true; 
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        this.setBounds(0,0,screenSize.width, screenSize.height);
        this.setVisible(true);
        this.setPreferredSize(screenSize);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 
        addKeyListener(this); 
        setFocusable(true);
        requestFocusInWindow();
        
        panel = new JPanel(new BorderLayout());
        upper = new JPanel(new GridLayout());
        middle = new JPanel(null);
        middle.setBackground(Color.WHITE);
        panel.setBackground(Color.WHITE);
        panel.add(middle, BorderLayout.CENTER);
        this.add(panel);
        
      //Button setups
        restraintStatus = new JButton1("<html> R:<br />RESTRAINTS UNLOCKED</html>");
        cyclePercent = new JButton1("% status");
        rideStatus = new JButton1("STATUS: Running");   
        degree = new JButton1("angle: 100 degrees");
        rectangle = new JPanel();
        rectangle2 = new JPanel();
        indicator = new JButton1("<html> NOT READY<br />For Ride Start</html>");
        reset = new JButton1("RESET"); 
        
        
        //setup classic tab
        classic = new JButton1("classic");
        classic.setPreferredSize(new Dimension
            (screenSize.width/2,screenSize.height/5));
        classic.setBorderPainted(false);
        classic.setBackground(Color.WHITE);   
        
        //setup advanced tab
        advanced = new JButton1("advanced diagnostics (Maintenance)");
        advanced.setPreferredSize(new Dimension
            (screenSize.width / 2, screenSize.height / 5));
        advanced.setBorderPainted(false);
        advanced.setBackground(new Color(204,204,204));
        direction = new JButton("direction: ");
        cyclesRun = new JButton("cycles run");
       
        
        panel.add(upper, BorderLayout.NORTH);
        upper.add(classic);
        upper.add(advanced);
        
        advanced.setBackground(new Color(204,204,204));
        classic.setBackground(Color.WHITE);
        
        
        
        restraintStatus.setBounds(30, 50, 600, 200);
        degree.setBounds(30, 50, 600, 85);
        
        cyclePercent.setBounds(650,165,600,85); 
        
        rideStatus.setBounds(650,50,600,85);

        JLabel row2 = new JLabel("Row 2: Back");
        row2.setBounds(30, 350, 780, 20);
        rectangle.setBounds(110, 350, 650, 20);
        rectangle.setBackground(Color.GREEN);
        middle.add(rectangle);
        middle.add(row2);
        
        JLabel row1 = new JLabel("Row 1: Front");
        row1.setBounds(30, 400, 780, 20);
        rectangle2.setBounds(110, 400, 650, 20);
        rectangle2.setBackground(Color.GREEN);
        middle.add(rectangle2);
        middle.add(row1);
        
        popup = new JFrame();
        popup.setBounds(500, 200, 300, 300);
        popup.setPreferredSize(new Dimension(300,300));
        popup.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);  
        setFocusable(true);
        popup.requestFocusInWindow();
        
        popupPanel = new JPanel();
        popup.add(popupPanel);
        password = new JTextField("password");
        popupPanel.add(password);
        
        indicator.setBounds(800, 312, 150, 150);
        middle.add(indicator);
        indicator.setBackground(Color.RED);
        
        errorBox = new JButton1("error messages");
        init = new JButton1("<html> 1<br />INIT</html>");
        auto = new JButton1("<html> 2<br />AUTO</html>");
        maint = new JButton1("<html> 3<br />MAINT</html>");
        off = new JButton1("<html> 4<br />OFF</html>");
        
        errorBox.setBounds(0, 480, 875, 100);
        middle.add(errorBox);
        init.setBounds(875, 480, 100, 100);
        middle.add(init);
        auto.setBounds(975, 480, 100, 100);
        middle.add(auto);
        maint.setBounds(1075, 480, 100, 100);
        middle.add(maint);
        off.setBounds(1175, 480, 100, 100);
        middle.add(off);
        
        init.setBackground(new Color(192, 192, 192));
        auto.setBackground(Color.WHITE);
        maint.setBackground(Color.WHITE);
        off.setBackground(Color.WHITE);
        
        //circle animation setup
        CirclePanel circle = new CirclePanel();
        circle.setBounds(1000, 312, 150, 150);
        middle.add(circle);
        
        //progress bar setup
        progressBarBase = new JPanel();
        progressBarBase.setBackground(Color.WHITE);
        progressBarBase.setBorder(BorderFactory.createLineBorder(Color.BLACK));
        progressBarBase.setBounds(100, 270, screenSize.width-200 , 30);
        progressBar = new JPanel();
        progressBar.setBackground(Color.GRAY);

        backEnd = new HMI_BackE();
        backEnd.startCyclePercent();

        timer = new Timer();
        
        TimerTask task = new TimerTask() {
            @Override
            public void run() {
                //TODO: fill in values for visual updates:
                int percent = backEnd.getCyclePercent(); // added
                cyclePercent.setText(percent + "% through cycle");
                cyclePercent.repaint();
                
                //updating status
                if(true/*TODO: status is running*/)
                    rideStatus.setText("STATUS: RUNNING");
                else if(true/*TODO:status is loading*/) {
                    rideStatus.setText("STATUS: LOADING");
                }
                else rideStatus.setText("STATUS: DOWN");
                
                //updating restraints
                if(true/*TODO: row1 is locked*/)
                    rectangle.setBackground(Color.GREEN);
                else rectangle.setBackground(Color.RED);
                
                if(false/*TODO: row2 is locked*/)
                    rectangle2.setBackground(Color.GREEN);
                else rectangle2.setBackground(Color.RED);
                
                if(false/*TODO: rows locked && correct mode && ready*/) {
                    indicator.setBackground(Color.GREEN);
                    indicator.setText("<html> READY<br />For Ride Start</html>");
                }
                else indicator.setBackground(Color.RED);
                
                
                //TODO: 
                //Use if else statements after code below to account for all errors
                if(true/* TODO: error condition 1*/)
                    errorBox.setText("display error message 1");
                else if(true/*TODO: error condition 2*/)
                    errorBox.setText("display error message 2");
                //...
                
                //If password is accepted:
                //note: irl, password would be hashed
                if(password.getText().equals("tpedhmi")) {
                    popup.dispatchEvent(new WindowEvent(popup, WindowEvent.WINDOW_CLOSING));
                    requestFocusInWindow();
                    paintAdvanced();
                    init.setBackground(Color.WHITE);
                    auto.setBackground(Color.WHITE);
                    maint.setBackground(new Color(192, 192, 192));
                    off.setBackground(Color.WHITE);
                    password.setText("password");
                }
                
                //Animation
                circle.paintLine(0/*TODO: insert function to get angle in radian*/);
                
                //ADVANCED DIAGNOSTICS FUNCTIONS
                progressBar.setBounds(100, 270, 
                    0/*TODO: get percent from backend*/*(screenSize.width-200), 30);
            }
        };
        
        //TODO: how often should visuals update? I have it set to 1% of the ride
        //cycle, which is 1.538 seconds, but unsure if it should update more
        timer.schedule(task, 1, 1538);
        
        
        paintClassic();
    }
    
    public void paintClassic() {
        
        isClassic = true;
        middle.add(rideStatus);
        middle.add(restraintStatus);
        middle.add(cyclePercent);
        middle.remove(degree);
        middle.remove(progressBar);
        middle.remove(progressBarBase);
        middle.repaint();
        advanced.setBackground(new Color(204,204,204));
        classic.setBackground(Color.WHITE);
        
    }
    
    public void paintAdvanced() {
        
        isClassic = false;
        middle.remove(restraintStatus);
        middle.remove(cyclePercent);
        
        middle.add(degree);
        middle.add(progressBarBase);
        middle.add(progressBar);

        middle.repaint();
        
        classic.setBackground(new Color(204,204,204));
        advanced.setBackground(Color.WHITE);
        
        
    }
    
    @Override
    public void keyPressed(KeyEvent e) {
        
        int key = e.getKeyCode();
        
        //TODO: Get rid of this once maintenance mode is done, its a backdoor
        if (key == KeyEvent.VK_M) {
            if(isClassic)
                paintAdvanced();
            else if(!isClassic)
                paintClassic();
        }
        
        if (key == KeyEvent.VK_R) {
            System.out.println("hi1");
            //TODO:
            //insert code to lock restraints
            if(restraintStatus.getText().equals("<html> R:<br />RESTRAINTS UNLOCKED</html>") && 
                true /*check if ride has been locked on backend*/)
                restraintStatus.setText("<html> R:<br />RESTRAINTS LOCKED</html>");
            else if(restraintStatus.getText().equals("<html> R:<br />RESTRAINTS LOCKED</html>") && 
                true /*check if ride has been unlocked on backend*/)
                restraintStatus.setText("<html> R:<br />RESTRAINTS UNLOCKED</html>");
            
            
        }

        if (key == KeyEvent.VK_1) {       
            init.setBackground(new Color(192, 192, 192));
            auto.setBackground(Color.WHITE);
            maint.setBackground(Color.WHITE);
            off.setBackground(Color.WHITE);
            paintClassic();
            //TODO:
            //activate init
            
        }
        if (key == KeyEvent.VK_2) {
            init.setBackground(Color.WHITE);
            auto.setBackground(new Color(192, 192, 192));
            maint.setBackground(Color.WHITE);
            off.setBackground(Color.WHITE);
            paintClassic();
            
            //TODO: 
            //activate auto
        }

        if (key == KeyEvent.VK_3) {
           
            popup.setVisible(true);
            
            
            //TODO:
            //activate maintenance
            
        } //KeyEvent 3
        
        if(key == KeyEvent.VK_4) { 
            
            init.setBackground(Color.WHITE);
            auto.setBackground(Color.WHITE);
            maint.setBackground(Color.WHITE);
            off.setBackground(new Color(192, 192, 192));
            paintClassic();
            //TODO:
            //turn off
        }
    }
    
    @Override
    public void keyReleased(KeyEvent e) { /* ... */ }
    
    @Override
    public void keyTyped(KeyEvent e) { /* ... */ }

}

//Ignore this for now, may be used to change the infill of the panels
class JButton1 extends JButton{
    
    public JButton1(String s) {
        super(s);
        //setContentAreaFilled(false);
        //this.setEnabled(false);
    }
    
}

class CirclePanel extends JPanel {
    @Override
    public void paintComponent(Graphics g) {
        this.setBackground(Color.WHITE);
        super.paintComponent(g);
        int x = 0; // top left corner
        int y = 0; // top left corner
        int d = 150; // Diameter of the circle

        g.setColor(Color.BLACK); // Set circle color
        g.drawOval(x, y, d, d); // Draw the circle outline
        // g.fillOval(x, y, diameter, diameter); // To draw a filled circle
        
        
    }
    
    public void paintLine(double angle){
        //this.setColor(Color.BLACK); // Set line color
        Line2D.Double line1 = new Line2D.Double(75, 75, (75*Math.cos(angle))+75, (-75*Math.sin(angle))+75);
        ((Graphics2D)this.getGraphics()).draw(line1);
        
    }
    
}

    
        