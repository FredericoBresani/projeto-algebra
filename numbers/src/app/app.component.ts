import { CommonModule } from '@angular/common';
import { Component, OnInit } from '@angular/core';
import { RouterOutlet } from '@angular/router';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [RouterOutlet, CommonModule],
  templateUrl: './app.component.html',
  styleUrl: './app.component.scss'
})
export class AppComponent  implements OnInit {
  
  public title = 'numbers';

  public numbers: number[] = [0];

  public mantissaLength: number = 0;

  public lengthOptions: { text: string; value: number }[] = [];

  public mantissa: number = 0;

  public validMantissaLength: boolean = false;

  public negativeNumbers: number[] = [];

  public positiveNumbers: number[] = [];

  public mantissas: number[] = [];

  public kmax: number = 0;

  public kmin: number = 0;

  public scope = 1;

  public minNumber = 0;

  public maxNumber = 0;
  
  constructor() {}

  public ngOnInit(): void {
    this.setLengthOptions();
  }

  public setLengthOptions(): void {
    for (let i = 1; i <= 100; i++) {
      this.lengthOptions.push({ text: i.toString(), value: i });
    }
  }

  public setScope(): void {
    while((this.scope*this.minNumber) < this.maxNumber) {
      this.scope *= 2;
    }
  }

  public setupMinAndMax(): void {
    this.minNumber = Math.pow(10, this.kmin - this.mantissaLength);
    this.maxNumber = 9;
    for (let i = 0; i < this.mantissaLength - 1; i++) {
      if (i < this.kmax - 1) {
        this.maxNumber = this.maxNumber * 10;
        this.maxNumber += 9;
      }
    }
    for (let i = this.mantissaLength; i < this.kmax; i++) {
      this.maxNumber *= 10;
    }
    this.setScope();
    if (this.validSetup()) this.generateNumbers();
  }

  public openOrCloseOptions(event: Event): void {
    const targetedElement: HTMLElement = event.target as HTMLElement;
    if (targetedElement.getAttribute('class') == 'option') {
      targetedElement.parentElement?.classList.toggle('active-options');
    } else {
      (targetedElement.lastChild as HTMLElement).classList.toggle('active-options');
    }
  }

  public setMantissaLength(n: number): void {
    this.mantissaLength = n;
    if (this.kmin != 0 && this.kmax != 0) this.setupMinAndMax();
    if (this.validSetup()) this.generateNumbers();
  }

  public checkMantissaLength(event: Event): void {
    if ((event.target as  HTMLInputElement).value?.length < this.mantissaLength) {
      this.validMantissaLength = true;
    } else {
      this.validMantissaLength = false;
    }
  }

  public validSetup(): boolean {
    return (this.mantissaLength != 0 && this.kmin != 0 && this.kmax != 0);
  }

  public updatekminValue(event: Event): void {
    this.kmin = Number((event.target as HTMLInputElement).value);
    if (this.kmax != 0 && this.mantissaLength != 0) this.setupMinAndMax();
  }

  public updatekmaxValue(event: Event): void {
    this.kmax = Number((event.target as HTMLInputElement).value);
    if (this.kmin != 0 && this.mantissaLength != 0) this.setupMinAndMax();
  }

  public zoomUp(): void {
    if (this.validSetup()) {
      if (this.scope > 1) {
        this.scope = this.scope / 2;
        this.generateNumbers();
      }
    }
  }

  public zoomDown(): void {
    if (this.validSetup()) {
      if (this.scope * this.minNumber < this.maxNumber) {
        this.scope = this.scope * 2;
        this.generateNumbers();
      }
    }
  }

  public generateNumbers(): void {
    this.positiveNumbers = [];
    this.negativeNumbers = [];
    let addedLast = false;
    for (let i = 0, j = 0; j < 5 && !addedLast; i += (this.minNumber*this.scope), j++) {
      if (i >= this.maxNumber) {
        this.positiveNumbers.push(this.maxNumber);
        this.negativeNumbers.push(-this.maxNumber);
        addedLast = true;
      } else {
        let temp = i;
        if (Math.round(i).toString().length >= this.mantissaLength) {
          temp = temp/Math.pow(10, Math.round(i).toString().length - this.mantissaLength);
          temp = Number(Math.round(temp));
          temp = temp*Math.pow(10, Math.round(i).toString().length - this.mantissaLength);
          this.positiveNumbers.push(temp);
          this.negativeNumbers.push(-temp); 
        } else {
          if (i < 1) {
            let leftZeroCounter = 0;
            let passedPoint = false;
            let hasLeftZeros = true;
            for (let j = 0; j < i.toString().length && hasLeftZeros; j++) {
              if (i.toString().at(j) == '.') {
                passedPoint = true;
              }
              if (passedPoint) {
                if (i.toString().at(j) == '0') {
                  leftZeroCounter++;
                } else if (i.toString().at(j) != '.'){
                  hasLeftZeros = false;
                }
              }
            }
            if (leftZeroCounter > 0) {
              this.positiveNumbers.push(Number((i).toFixed(this.mantissaLength + (leftZeroCounter > -this.kmin ? -this.kmin : leftZeroCounter))));
              this.negativeNumbers.push(Number((-i).toFixed(this.mantissaLength + (leftZeroCounter > -this.kmin ? -this.kmin : leftZeroCounter))));
            } else {
              this.positiveNumbers.push(Number((i).toFixed(this.mantissaLength)));
              this.negativeNumbers.push(Number((-i).toFixed(this.mantissaLength)));
            }
          } else {
            this.positiveNumbers.push(Number((i).toFixed(this.mantissaLength - Math.round(i).toString().length)));
            this.negativeNumbers.push(Number((-i).toFixed(this.mantissaLength - Math.round(i).toString().length)));
          }   
        }
      }
    }

    this.negativeNumbers = this.negativeNumbers.reverse();
    this.positiveNumbers.splice(0, 1);
    
    this.mantissas = [];
    this.mantissas.push(...this.negativeNumbers);
    this.mantissas.push(...this.positiveNumbers);
    for (let i = 0; i < this.mantissas.length; i++) {
      while(this.mantissas.indexOf(this.mantissas[i]) > i) {
        this.mantissas.splice(this.mantissas.indexOf(this.mantissas[i]), 1);
      }
    }
  }
}
