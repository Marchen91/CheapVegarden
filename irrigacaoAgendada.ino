void irrigacaoAgendada() {
Serial.println("Status da Solenoide Antes Ligação: ");
Serial.println(statusSolenoide);
if(statusSolenoide==1){
  ligarSolenoide();
          }
else{
  desligarSolenoide();
   } 
}
