   M S B A M L   `   `   `  ����b  ^Projet_Robot_interface_turbo_PRVST_RMSK, Version=1.0.0.0, Culture=neutral, PublicKeyToken=nulla5clr-namespace:Projet_Robot_interface_turbo_PRVST_RMSK'Projet_Robot_interface_turbo_PRVST_RMSK  5   	   8    2Projet_Robot_interface_turbo_PRVST_RMSK.MainWindow   5   	   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   Glocal5clr-namespace:Projet_Robot_interface_turbo_PRVST_RMSK     5   	     � Title$  
MainWindow��5   	   $	��450��6   $	��800��6)   .��5	      �  � RowDefinitions 5
   
   �� 5      $��30 �6   �� 5      �� 5      $��30 �6   �� 5      $��30 �6   �� 5      $��30 �6    � ColumnDefinitions 5   
   �� 5      $��30 �6   �� 5      �� 5      $��30 �6   �� 5      �� 5      $��30 �6   .+�5   
   �� $��GroupEmission��6   $��0q�6*   ���	#FFDDDDDD
���   �$��1��6`   $��1��6p   .��5      �� -   5         ��Name$ TextBoxEmission��5      $��0q�6/    �� TextWrapping$
 Wrap=�6:    �� AcceptsReturn . ��6p   Z� ��6�   Z� 6�   5      �� 5   
   -   5         ��Name$ GroupReception��5      $��	Reception��6+   $��0q�6>   ���	#FFDDDDDD
���   �$��3��6t   $��1��6�   .��5      �� -   5        $ TextBoxReception��5      $��0q�60   $
 Wrap=�6;    �� 
IsReadOnly . ��.   �� IsUndoEnabled .  ��6s   Z� ��6�   Z� 6�   5      �� 5   
   -   5        	 ��Name$	 buttonEnvoyer��5      $��Envoyer��6(   $��1��6:   $��Center=�6J   $��0q�6g   $��3��6r   $	��Top=�6   $	��100��6�   $��30��6�   6�   5       5!      